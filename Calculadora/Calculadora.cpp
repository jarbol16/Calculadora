// Calculadora.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "conio.h"//Para habilitar enyrada de datos en la terminal
#include "stdio.h"
#include "stdlib.h"
#include "iostream"

using namespace std;

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
	}
	printf("Respuesta= : %.2f\n", result);
	return 0.0;
divCero:
	cout << "|<     Division por cero     >|" << endl;
	return 0.0;
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


float exponente(float x,float e){
	float acum ;
	float cont = 1;
	float cero = 0.0;
	float Nuno = 1;
	__asm {
		FLD DWORD PTR[cero]
		FLD DWORD PTR[e]
		FCOMIP ST(0),ST(1)
		JE uno
		JMP inicio
	uno:
		FLD DWORD PTR[Nuno]//Leo el coeficiente
		FSTP DWORD PTR[acum]//guardo en acum el valor de x
		JMP terminar
	inicio:
		FLD DWORD PTR[x]//Leo el coeficiente
		FSTP DWORD PTR[acum]//guardo en acum el valor de x
	ciclo:
		FLD DWORD PTR[e]
		FLD DWORD PTR[cont]
		FCOMIP ST(0), ST(1)
		JE terminar
		FLD DWORD PTR[x]
		FLD DWORD PTR[acum]
		FMUL
		FSTP DWORD PTR[acum]
		FLD1
		FLD DWORD PTR[cont]
		FADD
		FSTP DWORD PTR[cont]
		JMP ciclo
	}

terminar:
	return acum;
}

float factorial(float a) {
	float cont = 1.000000;
	float cero = 0.0;
	float result = 1;
	__asm {
		FlD DWORD PTR[cero]
		FLD DWORD PTR[a]
		FCOMIP ST(0),ST(1)
		JE terminar
		JMP fact

	fact:
		FlD DWORD PTR(result)
		FLD DWORD PTR(cont)
		FMUL
		FSTP DWORD PTR(result)
		INC DWORD PTR(cont)
		FLD DWORD PTR(a)
		FLD DWORD PTR(cont)
		FCOMIP ST(0),ST(1)
		JE terminar
		JMP fact
	}
terminar:
	cout << cont;
	return result;
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
float seno(float x) {
	__asm {

	}
	return 0.0;
}

float coseno(float x) {
	__asm {

	}
	return 0;
}

float tangente(float x) {
	__asm {
		
	}
	return 0;
}


	


int main()
{
menu:int op;
	float a, b;
	cout << "|   CALCULADORA CIENTIFICA    |" << endl;
	cout << "|-----------------------------|" << endl;
	cout << "| OPERACIONES SOPORTADAS:     |" << endl;
	cout << "|_____________________________|" << endl;
	cout << "|>SUMA                     1  |" << endl;
	cout << "|>RESTA                    2  |" << endl;
	cout << "|>MULTIPLICACION           3  |" << endl;
	cout << "|>DIVISION                 4  |" << endl;
	cout << "|>SENO                     5  |" << endl;
	cout << "|>COSENO                   6  |" << endl;
	cout << "|>TANGENTE                 7  |" << endl;
	cout << "|>RAIZ CUADRADA            8  |" << endl;
	cout << "|>EXPONENTE                9  |" << endl;
	cout << "|>LOG BASE 2              10  |" << endl;
	cout << "|>LOG BASE 10             11  |" << endl;
	cout << "|>e^x                     12  |" << endl;
	cout << "|>FACTORIAL               13  |" << endl;
	cout << "|DIGITE OPCION:               |" << endl;
	cout << "|_____________________________|" << endl;
	cin >> op;

	switch (op){
		case 1:
			cout << "|             SUMA            |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite primer numero:";
			cin >> a;
			cout << "| Digite segundo numero:";
			cin >> b;
			cout << "| Respuesta = " << sumar(a, b)<<endl;
			goto seguir;
		case 2:
			cout << "|            RESTA            |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite primer numero:";
			cin >> a;
			cout << "| Digite segundo numero:";
			cin >> b;
			cout << "| Respuesta = " << resta(a, b) << endl;
			goto seguir;
		case 3:
			cout << "|       MULTIPLICACION        |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite primer numero:";
			cin >> a;
			cout << "| Digite segundo numero:";
			cin >> b;
			cout << "| Respuesta = " << multiplicacion(b, a) << endl;
			goto seguir;
		case 4:
			cout << "|           DIVISION          |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite primer numero:";
			cin >> a;
			cout << "| Digite segundo numero:";
			cin >> b;
			division(a,b);
			goto seguir;
		case 5:
			cout << "|              SENO           |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite  numero:";
			cin >> a;
			cout << "| Respuesta = " << seno(a) << endl;
			goto seguir;
		case 6:
			cout << "|            COSENO           |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite  numero:";
			cin >> a;
			cout << "| Respuesta = " << coseno(a) << endl;
			goto seguir;
		case 7:
			cout << "|          TANGENTE           |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite  numero:";
			cin >> a;
			cout << "| Respuesta = " << tangente(a) << endl;
			goto seguir;
		case 8:
			cout << "|       RAIZ CUADRADA         |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite  numero:";
			cin >> a;
			b = raiz(a);
			if (b < 0) {
				cout << "|<No soporta imaginarios>|" << endl;
			}else { 
				cout << "Respuesta =" << b  << endl;
			}
			goto seguir;

		case 9:
			cout << "|          EXPONENTE          |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite coeficiente:";
			cin >> a;
			cout << "| Digite exponente:";
			cin >> b;
			cout << "| Respuesta =" << exponente(a, b) << endl;
			goto seguir;
		case 10:
		case 11:
		case 12:
		case 13:
			int fac;
			cout << "|         FACTORIAL           |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite  numero:" << endl;
			cin >> fac;
			if (fac < 0) {
				fac = fac*-1;
				cout << "| Respuesta = -" << factEntero(fac) << endl;
			}else {
				cout << "| Respuesta = " << factEntero(fac) << endl;
			}
			goto seguir;
		default:
			break;
	}

seguir:op = 0;
	cout << "|-----------------------------|" << endl;
	cout << "|Desea continuar si(1) - No(0)|" << endl;
	cin >> op;
	if (op == 1){
		goto menu;
	}
	return 0;
}

