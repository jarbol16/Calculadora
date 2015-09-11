// Calculadora.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "conio.h"//Para habilitar enyrada de datos en la terminal
#include "stdio.h"
#include "stdlib.h"
#include "iostream"

using namespace std;

int sumar(int a, int b){//luego hay que ponerlo como flotante
	int result;
	__asm {
		mov eax,a // se mueve el valor de a al eax
		add eax,b// e mueve el valor de b al eax y se suma
		mov result, eax // se guarda el resultado en la variable
	}
	return result;
}

int resta(int a, int b) {
	int result;
	__asm {
		mov eax, a
		sub eax, b
		mov result, eax
	}
	return result;
}

int multiplicacion(int a, int b) {
	__asm {

	}
	return 0;
}

int division(int a, int b) {
	__asm {

	}
	return 0;
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
menu:int a, b,op;
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
			cout << "| Respuesta = " << division(b, a) << endl;
			goto seguir;
		case 5:
			cout << "|              SENO           |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite primer numero:";
			cin >> a;
			cout << "| Respuesta = " << seno(a) << endl;
			goto seguir;
		case 6:
			cout << "|            COSENO           |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite primer numero:";
			cin >> a;
			cout << "| Respuesta = " << coseno(a) << endl;
			goto seguir;
		case 7:
			cout << "|          TANGENTE           |" << endl;
			cout << "|-----------------------------|" << endl;
			cout << "| Digite primer numero:";
			cin >> a;
			cout << "| Respuesta = " << tangente(a) << endl;
			goto seguir;
		case 8:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
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

