// Calculadora.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "conio.h"//Para habilitar enyrada de datos en la terminal
#include "stdio.h"
#include "stdlib.h"
#include "iostream"
using namespace std;
void paso() {
	cout << "PASO" << endl;
}
float sumar(float a, float b){//luego hay que ponerlo como flotante
	float result = 0.00;
	__asm {
		FLD dword ptr[a] // guardo temporamente en el stack el valor flotante de a
		FLD dword ptr[b]// guardo temporamente en el stack el valor flotante de b
		FADD // sumo los ultimos dos valores guardados en el stack
		FSTP dword ptr[result] // traigo el resulto y lo alamaceno en la variable
	}
	return result;
}

float resta(float a, float b) {
	float result;
	__asm {
		FLD DWORD PTR[a] // guardo temporamente en el stack el valor flotante de a
		FLD DWORD PTR[b] // guardo temporamente en el stack el valor flotante de b
		FSUB // resto los ultimos dos valores guardados en el stack
		FSTP DWORD PTR[result]// traigo el resulto y lo alamaceno en la variable
	}
	return result;
}

float multiplicacion(float a, float b) {
	float result;
	__asm {
		FLD DWORD PTR[a]
		FLD DWORD PTR[b]
		FMUL
		FSTP DWORD PTR[result]
	}
	return result;
}

float division(float a, float b) {
	float cero = 0.0;
	float result;
	__asm {
		FLD DWORD PTR[b]
		FLD DWORD PTR[cero]
		FCOMIP ST(0), ST(1)
		JE divCero
		FLD DWORD PTR[a]
		FLD DWORD PTR[b]
		FDIV
		FSTP DWORD PTR[result]
		JO overf
		JC fin
	}
	fin:
	printf("| Respuesta= : %.2f\n", result);
	return result;
divCero:
	cout << "|<     Division por cero     >|" << endl;
	return 0.0;
overf:
	cout << "|<     -----Overflow-----    >|" << endl;
}

float raiz(float x) {
	float result=-1.0;
	float cero = 0.0;
	__asm {
		FLD DWORD PTR[cero];
		FLD DWORD PTR[x];
		FCOMIP ST(0), ST(1);
		JA positivo;
		JMP terminar;
	positivo:
		FLD DWORD PTR[x];
		FSQRT
		FSTP DWORD PTR[result]
		JMP terminar;
	}
 
terminar:
	return result;
}
/*
Mtodo de la raiz por medio de iteraciones
*/
float raiz_metodo(float x) {
	float result =0.0;
	float cero = 0.0;
	float tmpo = 0.0;
	float d = 2.0; 
	__asm {
		FLD DWORD PTR[cero];
		FLD DWORD PTR[x];
		FCOMIP ST(0), ST(1);
		fstp ST(0) // limpio el stack
		JA inicio
		JMP terminar;

	inicio:
		FLD DWORD PTR[x]
		FSTP DWORD PTR[result]
		JMP ciclo

	ciclo:
		FLD DWORD PTR[result];
		FLD DWORD PTR[tmpo];
		FCOMIP ST(0), ST(1);
		FSTP ST(0) //LIMPIO
		JE terminar;
		FLD DWORD PTR[result];
		FSTP DWORD PTR[tmpo]; //TMPO = RES
		FLD DWORD PTR[x]; //METO RES EN EL STACK
		FDIV DWORD PTR[result]; //   BASE/RES
		FADD DWORD PTR[result]; // BASE/RES + RES
		FDIV DWORD PTR[d]; // (BASE/RES + RES)/2
		FSTP DWORD PTR[result]; //RES = (BASE/RES + RES)/2
		JMP ciclo;
	}

terminar:
	return result;
}
float exponente_flotante(float base, float exp) {
	float result = 0.0f;
	float cero = 0.0f;
	__asm {
		FLD DWORD PTR[cero] //cargo tmpres
		FLD DWORD PTR[base] //cargo cero
		FCOMIP ST(0), ST(1); //comparo tmpres y cero
		FSTP ST(0) //limpio y
		JL positive //si es 0, fin
		JMP negative
			positive:
		FLD DWORD PTR[exp]//leo LA POTENCIA
		FLD DWORD PTR[base]//leo la base
		FYL2X
		FLD ST
		FRNDINT//redondeo a entero
		FSUB ST(1),ST //se resta el valor de st(1) a st para obtener parte decimal
		FXCH ST(1)//intercambio el valor del stack cero por el stack 1
		F2XM1//calcula valor de 2^x-1
		FLD1//cargo valor de 1
		FADD//sumo el 1 para que quede 2^x
		FSCALE
		FSTP DWORD PTR[result]
		JMP exp_fin
		negative:
		MOV eax, DWORD PTR[exp] //El
		PUSH eax //Exponente
		MOV eax, DWORD PTR[base] //La
		PUSH eax //Base
		CALL powf //Llamo la funcion
		POP ebx
		POP ebx
		FSTP DWORD PTR[result] //Guardo el x^n
		exp_fin:
	}
	return result;
}

float factorial(float n){
	n = abs(roundf(n));
	float f = 1.f;
	if (n==0.f || n==1.f) return 1.0f;
	for (float i = 1.f; i <= n; i = i + 1.f) {
		f = f*i;
	}
	return f;
}

int factEntero(int X) {
	int cero = 0, uno = 1, nega = -1;
	int result = 1;

	__asm{
		MOV EAX, X;
		CMP EAX, cero;
		JE igual; //SI X=0 VAYA

  ciclo: 
		INC ECX; //INCREMETO I
		MOV EAX, result; // CARGAR RESULTADO
		MUL ECX; //MULTIPLICAR POR EL ITERADOR
		MOV result, EAX; //RES = RES*I
		CMP ECX, X; // ECX == X
		JE terminar;
		JMP ciclo;

  igual: MOV EAX, uno;
		MOV result, EAX;
		JMP terminar;
  }
terminar:
	return result;
}

float gradosARadianes(float n) {
	n = fmod(n, 360.0f); //Convierto a angulo de -360° a +360°
	if (n < 0) n += 360.f; //Convierto a angulos positivos
	float pi = 3.14159265358979323846f;
	float a = 180.0f;
	float mult;
	float result;
	__asm {
			FLD DWORD PTR[n]
			FLD DWORD PTR[pi]
			FMUL
			FSTP DWORD PTR[mult]
			FLD DWORD PTR[mult]
			FLD DWORD PTR[a]
			FDIV
			FSTP DWORD PTR[result]
	}
	return result;
}

float seno_intel(float x) {
	x = gradosARadianes(x);
	float result = 0.0;
	__asm {
		FLD DWORD PTR[x]
			FSIN
			FSTP DWORD PTR[result];
	}
	return result;
}

float seno_metodo(float x) {
	float n = gradosARadianes(x);
	float dos = 2.f;
	int niter = 10;
	float exp = 3.f;
	float menosuno = -1.f;
	float res = 0.0;
	float xn = 0.f;
	float iterador = 0.f;
	float nf;
	float p;
	float signo = menosuno;

	__asm {

	ciclo:
			INC iterador
			MOV eax, DWORD PTR[exp] //El
			PUSH eax //Exponente
			MOV eax, DWORD PTR[n] //La
			PUSH eax //Base
			CALL powf //Llamo la funcion
			POP ebx
			POP ebx
			FSTP DWORD PTR[xn] //Guardo el x^n
			MOV eax, DWORD PTR[exp]
			PUSH eax // el exp
			CALL factorial //hago exp!
			POP ebx
			FSTP DWORD PTR[nf] // guardo el n!
			FLD DWORD PTR[xn]
			FLD DWORD PTR[nf]
			FDIV
			FSTP DWORD PTR[p]

			FLD DWORD PTR[signo]
			FLD DWORD PTR[p]
			FMUL
			FSTP DWORD PTR[p] // signo de la fracción
			FLD dword ptr[res] 
			FLD dword ptr[p]
			FADD 
			FSTP dword ptr[res]// resultado parcial
			FLD dword ptr[exp]
			FLD dword ptr[dos]
			FADD
			FSTP dword ptr[exp]
			FLD DWORD PTR[signo]
			FLD DWORD PTR[menosuno]
			FMUL
			FSTP DWORD PTR[signo] // signo de la fracción
			MOV EAX, iterador
			CMP EAX, niter
			JE fin
			JMP ciclo

		fin:
			FLD DWORD PTR[n]
			FLD DWORD PTR[res] 
			FADD 
			FSTP DWORD PTR[res]	
	}

	return res;
}

float coseno_metodo(float x) {
	float n = gradosARadianes(x);
	float dos = 2.f;
	int niter = 10;
	float exp = 2.f;
	float menosuno = -1.f;
	float res = 0.0;
	float xn = 0.f;
	float iterador = 0.f;
	float nf;
	float p;
	float signo = menosuno;
	float uno = 1.f;

	__asm {

	ciclo:
		INC iterador
			MOV eax, DWORD PTR[exp] //El
			PUSH eax //Exponente
			MOV eax, DWORD PTR[n] //La
			PUSH eax //Base
			CALL powf //Llamo la funcion
			POP ebx
			POP ebx
			FSTP DWORD PTR[xn] //Guardo el x^n
			MOV eax, DWORD PTR[exp]
			PUSH eax // el exp
			CALL factorial //hago exp!
			POP ebx
			FSTP DWORD PTR[nf] // guardo el n!
			FLD DWORD PTR[xn]
			FLD DWORD PTR[nf]
			FDIV
			FSTP DWORD PTR[p]

			FLD DWORD PTR[signo]
			FLD DWORD PTR[p]
			FMUL
			FSTP DWORD PTR[p] // signo de la fracción
			FLD dword ptr[res]
			FLD dword ptr[p]
			FADD
			FSTP dword ptr[res]// resultado parcial
			FLD dword ptr[exp]
			FLD dword ptr[dos]
			FADD
			FSTP dword ptr[exp]
			FLD DWORD PTR[signo]
			FLD DWORD PTR[menosuno]
			FMUL
			FSTP DWORD PTR[signo] // signo de la fracción
			MOV EAX, iterador
			CMP EAX, niter
			JE fin
			JMP ciclo

		fin :
			FLD DWORD PTR[uno]
			FLD DWORD PTR[res]
			FADD
			FSTP DWORD PTR[res]
	}

	return res;
}
float coseno_intel(float x) {
	x = gradosARadianes(x);
	float result = 0.0;
	__asm {
		FLD DWORD PTR[x]
		FCOS
		FSTP DWORD PTR[result];
	}
	return result;
}

float tangente_intel(float x) {
	x = fmod(x, 360.0f); //Convierto a angulo de -360° a +360°
	if (x < 0) x += 360.f; //Convierto a angulos positivos
	if (x == 90.f || x == 270.0f) {
		cout << "| ALERT: Not A Number" << endl;
		return log(-1.f);
	}
	x = gradosARadianes(x);
	float result = 0.0;
	__asm {
		FLD DWORD PTR[x]
		FPTAN
		FSTP ST(0)
		FSTP DWORD PTR[result]
	}
	return result;
}
float tangente_metodo(float x) {
	x = fmod(x, 360.0f); //Convierto a angulo de -360° a +360°
	if (x < 0) x += 360.f; //Convierto a angulos positivos
	if (x == 90.f || x == 270.0f) {
		cout << "| ALERT: Not A Number" << endl;
		return log(-1.f);
	}
	float sin = 0.f;
	float cos = 0.f;
	float cero = 0.f;
	__asm {
		MOV eax, DWORD PTR[x]
		PUSH eax
		CALL seno_metodo
		POP ebx
		FSTP DWORD PTR[sin]
		MOV eax, DWORD PTR[x]
		PUSH eax
		CALL coseno_metodo
		POP ebx
		FSTP DWORD PTR[cos]
		FLD DWORD PTR[cero]
		FLD DWORD PTR[cos]
		FCOMIP ST(0), ST(1);
		FSTP ST(0)
		JE tan_infinity
		FLD DWORD PTR[sin] 
		FLD DWORD PTR[cos]
		FDIV
		FSTP DWORD PTR[cero]
		JMP fin
	}
	tan_infinity:
	cout << "| ALERT: Infinity" << endl;
		return tanf(x);
	fin:
	return cero;
}
/*
logaritmo base 10 con la implemtacion brindada por el 
procesador

*/
float log10_intel(float x) {
	float result;
	__asm {
		FLDLG2 //LOGARIT
		FLD DWORD PTR[x]
		FYl2X //parametro del procesador para calcular log10
		FSTP DWORD PTR[result]//Guardo el resultado en resultado
	}
	return result;
}

float log2_intel(float x) {
	float result;
	float uno = 1;
	__asm {
		FLD DWORD PTR[uno]
		FLD DWORD PTR[x]
		FYL2X
		FSTP DWORD PTR[result]
	}
	return result;
}

float series_ln(float x) {
	if(x>0.0f){
		goto follow;
	}
	else if (x == 0.0f) {
		goto lessinfinity;
	}
	else {
		goto nan_ln;
	}
	/*
		ln(x) = 2*sum from n=1 to inf of
		((x-1)/(x+1))**(2n-1) 
		--------------------
			   (2n-1)
		for x > 0
	*/
	follow:
	float result = 0.0f;
	float incremento = 1.f;
	float n = 0.0f;
	float top = 0.0f; //(x-1)/(x+1)
	float tmp1 = 0.0f;
	float tmp2 = 0.0f;
	float uno = 1.0f;
	float muno = -1.f;
	float cero = 0.0f;
	float dos = 2.f;
	float max_iter = 11.f;
	__asm { //(x-1)/(x+1)
		FLD DWORD PTR[uno]
		FLD DWORD PTR[x]
		FADD st(0),st(1) //(x+1)
		FSTP DWORD PTR[tmp2]
		FLD DWORD PTR[uno]
		FLD DWORD PTR[x]
		FSUB st(0),st(1) //(x-1)
		FSTP DWORD PTR[tmp1]
		FLD DWORD PTR[tmp2] // (x+1) st(1)
		FLD DWORD PTR[tmp1] // (x-1) st(0)
		FDIV st(0),st(1) // (x-1)/(x+1)
		FSTP DWORD PTR[top]
	}
	__asm {
	ciclo:
		FLD DWORD PTR[n] //n
		FLD DWORD PTR[uno] //+
		FADD
		FSTP DWORD PTR[n] //n+1
		FLD DWORD PTR[incremento] //Si el incremento es
		FLD DWORD PTR[cero] // cero
		FCOMIP st,st(1) //entonces
		FSTP ST(0) //limpio y 
		JE fin //termino
		FLD DWORD PTR[n] //si pongo n
		FLD DWORD PTR[dos] //lo multiplico por 2
		FMUL
		FSTP DWORD PTR[tmp2] //2n
		FLD DWORD PTR[tmp2] //le resto
		FLD DWORD PTR[muno] //uno
		FADD
		FSTP DWORD PTR[tmp2] 
		MOV EAX, DWORD PTR[tmp2] //exponente
		PUSH EAX
		MOV EAX, DWORD PTR[top] //base
		PUSH EAX
		CALL powf
		POP EBX
		POP EBX
		FSTP DWORD PTR[tmp1]
		FLD DWORD PTR[tmp1]
		FLD DWORD PTR[tmp2]
		FDIV
		FSTP DWORD PTR[incremento]
		FLD DWORD PTR[result]
		FLD DWORD PTR[incremento]
		FADD
		FSTP DWORD PTR[result]
		JO fin //Si hay overflow termino antes de sumar a result
		JMP ciclo
		fin:
		FLD DWORD PTR[result]
		FLD DWORD PTR[dos]
		FMUL
		FSTP DWORD PTR[result]
		JMP retu
	}
	lessinfinity:
		cout << "| ALERT: -infinity" << endl;
		return log(0.f);
	nan_ln:
		cout << "| ALERT: Not a Number" << endl;
		return log(-1.f);
	retu:
	return result;
}
float series_e(float x) {
	float result = 0.f;
	float n = -1.f;
	float uno = 1.0f;
	float cero = 0.0f;
	float tmpxn = 0.f;
	float tmpnf = 0.f;
	float tmpres = 0.f;
	__asm {
	ciclo:
		FLD DWORD PTR[n] //Cargo n
		FLD DWORD PTR[uno] //Cargo 1
		FADD //n+1
		//CALL paso
		FSTP DWORD PTR[n] //n=n+1
		MOV eax, DWORD PTR[n] //El
		PUSH eax //Exponente
		MOV eax, DWORD PTR[x] //La
		PUSH eax //Base
		CALL powf //Llamo la funcion
		POP ebx
		POP ebx
		FSTP DWORD PTR[tmpxn] //Guardo el x^n
		MOV eax, DWORD PTR[n]
		PUSH eax // el n
		CALL factorial //hago n!
		POP ebx
		FSTP DWORD PTR[tmpnf] // guardo el n!
		FLD DWORD PTR[tmpxn] //cargo x^n
		FLD DWORD PTR[tmpnf] // cargo el n!
		FDIV
		FSTP DWORD PTR[tmpres]
		JO fin
		FLD DWORD PTR[tmpres] //cargo tmpres
		FLD DWORD PTR[cero] //cargo cero
		FCOMIP ST(0), ST(1); //comparo tmpres y cero
		FSTP ST(0) //limpio y
		JE fin //si es 0, fin
		FLD DWORD PTR[result]
		FLD DWORD PTR[tmpres]
		FADD
		FSTP DWORD PTR[result]
		JMP ciclo // si no siga
	fin:	
	}
	return result;
}
float log10_metodo(float x) {
	float ten = 10.0f;
	float result = 0.0f;
	__asm {
		MOV eax, DWORD PTR[ten] //cargo 10
		PUSH eax // lo mando de parametro
		CALL series_ln //hago ln(10)
		POP ebx //quito el parametro
		FSTP DWORD PTR[ten] // guardo ln(10) donde estaba 10
		MOV eax, DWORD PTR[x] //cargo x
		PUSH eax // lo mando de parametro
		CALL series_ln //hago ln(x)
		POP ebx //quito el parametro
		FSTP DWORD PTR[result] // guardo ln(x) donde estaba result
		FLD DWORD PTR[result] //ln(x)
		FLD DWORD PTR[ten] // ln(10)
		FDIV //log10(x) = ln(x)/ln(10)
		FSTP DWORD PTR[result] 
	}
	return result;
}
float log2_metodo(float x) {
	float two = 2.0f;
	float result = 0.0f;
	__asm {
			MOV eax, DWORD PTR[two] //cargo 10
			PUSH eax // lo mando de parametro
			CALL series_ln //hago ln(10)
			POP ebx //quito el parametro
			FSTP DWORD PTR[two] // guardo ln(10) donde estaba 10
			MOV eax, DWORD PTR[x] //cargo x
			PUSH eax // lo mando de parametro
			CALL series_ln //hago ln(x)
			POP ebx //quito el parametro
			FSTP DWORD PTR[result] // guardo ln(x) donde estaba result
			FLD DWORD PTR[result] //ln(x)
			FLD DWORD PTR[two] // ln(10)
			FDIV //log10(x) = ln(x)/ln(10)
			FSTP DWORD PTR[result]
	}
	return result;
}
int main()
{
	cout << "|-----------------------------|" << endl;
	cout << "|    Calculadora en : DEG     |" << endl;
	cout << "|-----------------------------|" << endl;
menu:int op;
	float a, b;
	float alt;
	cout << "|   CALCULADORA CIENTIFICA    |" << endl;
	cout << "|-----------------------------|" << endl;
	cout << "| OPERACIONES SOPORTADAS:     |" << endl;
	cout << "|_____________________________|" << endl;
	cout << "| > SUMA                   1  |" << endl;
	cout << "| > RESTA                  2  |" << endl;
	cout << "| > MULTIPLICACION         3  |" << endl;
	cout << "| > DIVISION               4  |" << endl;
	cout << "| > SENO                   5  |" << endl;
	cout << "| > COSENO                 6  |" << endl;
	cout << "| > TANGENTE               7  |" << endl;
	cout << "| > RAIZ CUADRADA          8  |" << endl;
	cout << "| > EXPONENTE              9  |" << endl;
	cout << "| > FACTORIAL             10  |" << endl;
	cout << "| > LOG BASE 2            11  |" << endl;
	cout << "| > LOG BASE 10           12  |" << endl;
	cout << "| > e^x                   13  |" << endl;
	cout << "| > ln(x)                 14  |" << endl;
	cout << "| > SALIR                  0  |" << endl;
	cout << "|_____________________________|" << endl;
	cout << "| DIGITE OPCION:              |" << endl;
	cout << "|_____________________________|" << endl;
	cout << "| > "; cin >> op;
	op = op % 20;
	switch (op){
		case 1:
			cout << "|             SUMA            |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite primer numero: ";
			cin >> a;
			cout << "| Digite segundo numero: ";
			cin >> b;
			cout << "| Respuesta = " << sumar(a, b)<<endl;
			goto seguir;
		case 2:
			cout << "|            RESTA            |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite primer numero: ";
			cin >> a;
			cout << "| Digite segundo numero: ";
			cin >> b;
			cout << "| Respuesta = " << resta(a, b) << endl;
			goto seguir;
		case 3:
			cout << "|       MULTIPLICACION        |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite primer numero: ";
			cin >> a;
			cout << "| Digite segundo numero: ";
			cin >> b;
			cout << "| Respuesta = " << multiplicacion(b, a) << endl;
			goto seguir;
		case 4:
			cout << "|           DIVISION          |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite primer numero: ";
			cin >> a;
			cout << "| Digite segundo numero: ";
			cin >> b;
			division(a,b);
			goto seguir;
		case 5:
			cout << "|              SENO           |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite  numero: ";
			cin >> a;
			cout << "| [FP] Respuesta = " << seno_intel(a) << endl;
			cout << "| [ME] Respuesta = " << seno_metodo(a) << endl;
			goto seguir;
		case 6:
			cout << "|            COSENO           |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite  numero: ";
			cin >> a;
			cout << "| [FP] Respuesta = " << coseno_intel(a) << endl;
			cout << "| [ME] Respuesta = " << coseno_metodo(a) << endl;
			goto seguir;
		case 7:
			cout << "|          TANGENTE           |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite  numero: ";
			cin >> a;
			cout << "| [FP] Respuesta = " << tangente_intel(a) << endl;
			cout << "| [ME] Respuesta = " << tangente_metodo(a) << endl;
			goto seguir;
		case 8:
			cout << "|       RAIZ CUADRADA         |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite  numero: ";
			cin >> a;
			if (a < 0) {
			cout << "|         <ADVERTENCIA>       |" << endl;
			cout << "|   <No soporta imaginarios>  |" << endl;
			a *= -1.f;
			cout << "| [FP] Respuesta = " << raiz(a) << "i" << endl;
			cout << "| [ME] Respuesta = " << raiz_metodo(a)<< "i"<< endl;
			}else { 
				cout << "| [FP] Respuesta = " << raiz(a) << endl;
				cout << "| [ME] Respuesta = " << raiz_metodo(a) << endl;
			}
			goto seguir;

		case 9:
			cout << "|          EXPONENTE          |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite coeficiente: ";
			cin >> a;
			cout << "| Digite exponente: ";
			cin >> b;
			cout << "| Respuesta = " << exponente_flotante(a, b) << endl;
			goto seguir;
		case 10:
			cout << "|         FACTORIAL           |" << endl;
			cout << "|-----------------------------|" << endl;
			float fac;
			cout << "| Digite  numero: ";
			cin >> fac;
			if (fac < 0) {
			cout << "| ERROR: factoial no definido |"<< endl;
			cout << "|   en los numeros negativos  |" << endl;
			}else {
				float decimal = fmod(fac, 1.f);
				if (decimal == 0.0) {
					cout << "| Respuesta = " << factEntero((int)fac) << endl;
				}
				else {
			cout << "|ALERTA: Factorial no definido|" << endl;
			cout << "| se aproximo al entero menor |" << endl;
					cout << "| Respuesta = "<<
						factEntero((int)(fac-decimal)) << endl;
				}
				cout << "| Respuesta = " << factEntero((int)fac) << endl;
			}
			goto seguir;
		case 11:
			cout << "|        LOG BASE 2           |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite  numero: ";
			cin >> a;
			cout << "| [FP] Respuesta = " << log2_intel(a) << endl;
			cout << "| [ME] Respuesta = " << log2_metodo(a) << endl;
			goto seguir;
		case 12:
			cout << "|        LOG BASE 10          |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite  numero: ";
			cin >> a;
			cout << "| [FP] Respuesta = " << log10_intel(a) << endl;
			cout << "| [ME] Respuesta = " << log10_metodo(a) << endl;
			goto seguir;
		case 13:
			cout << "|            e^x              |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite  numero: ";
			float y; cin >> y;
			cout << "| Respuesta = " << series_e(y) << endl;
			goto seguir;
		case 14:
			cout << "|            ln(x)            |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite  numero: ";
			float l; cin >> l;
			cout << "| Respuesta = " << series_ln(l) << endl;
			goto seguir;
		case 0:
			return 0;
		default:
			goto seguir;
			break;
	}

seguir:
	cout << endl << endl << endl;
	goto menu;
	return 0;
}

