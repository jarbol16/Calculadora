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

/*
float exponente(float x,float e){
	float acum ;
	float cont = 1;
	float cero = 0.0;
	float Nuno = 1;
	__asm {
		FLD DWORD PTR[cero]
		FLD DWORD PTR[e]
		FCOMIP ST(0),ST(1)
		FSTP ST(0)
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
		FSTP ST(0)
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
}*/
float exponente_flotante(float a, float b) {
	float result;
	__asm {
		FLD DWORD PTR[b]//leo LA POTENCIA
		FLD DWORD PTR[a]//leo la base
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
	}
	return result;
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

float coseno_metodo(float x) {
	__asm {

	}
	return 0;
}
float coseno_intel(float x) {
	float result = 0.0;
	__asm {
		FLD DWORD PTR[x]
		FCOS
		FSTP DWORD PTR[result];
	}
	return result;
}

float tangente_intel(float x) {
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
	__asm {

	}
	return 0;
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
float log10_metodo(float x) {
	float result;
	__asm {

	}
	return 0.0;

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
float log2_metodo(float x) {
	float result;
	__asm {

	}
	return 0.0;

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
	cout << "|>FACTORIAL               10  |" << endl;
	cout << "|>LOG BASE 2              11  |" << endl;
	cout << "|>LOG BASE 10             12  |" << endl;
	cout << "|>e^x                     13  |" << endl;
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
			cout << "| [FP] Respuesta = " << seno(a) << endl;
			goto seguir;
		case 6:
			cout << "|            COSENO           |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite  numero:";
			cin >> a;
			cout << "| [FP] Respuesta = " << coseno_intel(a) << endl;
			cout << "| [ME] Respuesta = " << coseno_metodo(a) << endl;
			goto seguir;
		case 7:
			cout << "|          TANGENTE           |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite  numero:";
			cin >> a;
			cout << "| [FP] Respuesta = " << tangente_intel(a) << endl;
			cout << "| [ME] Respuesta = " << tangente_metodo(a) << endl;
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
				cout << "[FP] Respuesta =" << b  << endl;
				cout << "[ME] Respuesta =" << raiz_metodo(a) << endl;
			}
			goto seguir;

		case 9:
			cout << "|          EXPONENTE          |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite coeficiente:";
			cin >> a;
			cout << "| Digite exponente:";
			cin >> b;
			cout << "| Respuesta =" << exponente_flotante(a, b) << endl;
			goto seguir;
		case 10:
			cout << "|         FACTORIAL           |" << endl;
			cout << "|-----------------------------|" << endl;
			int fac;
			cout << "| Digite  numero:" << endl;
			cin >> fac;
			if (fac < 0) {
				fac = fac*-1;
				cout << "| Respuesta = -" << factEntero(fac) << endl;
			}else {
				cout << "| Respuesta = " << factEntero(fac) << endl;
			}
			goto seguir;
		case 12:
			cout << "|        LOG BASE 10          |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite  numero:";
			cin >> a;
			cout << "| [FP] Respuesta = " << log10_intel(a) << endl;
			cout << "| [ME] Respuesta = " << log10_metodo(a) << endl;
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

