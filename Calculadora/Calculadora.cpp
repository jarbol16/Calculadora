// Calculadora.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include "conio.h"//Para habilitar enyrada de datos en la terminal
#include "stdio.h"
#include "stdlib.h"
#include "iostream"

using namespace std;

float sumar(int a, int b){
	float result;
	__asm {
		mov eax,a // se mueve el valor de a al eax
		add eax,b// e mueve el valor de b al eax y se suma
		mov result, eax // se guarda el resultado en la variable
	}
	return result;
}

int main()
{
menu:int op,a, b;
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
			cout << "| Digite primer numero:       |" << endl;
			cin >> a;
			cout << "| Digite segundo numero:      |" << endl;
			cin >> b;
			printf("| Respuesta = ",sumar(a, b)," |");
			
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
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





	
    return 0;
}

