//guia https://msdn.microsoft.com/en-us/library/4ks26t93.aspx
//guia2 http://www.jegerlehner.ch/intel/IntelCodeTable_es.pdf no sirve para floats

#include <iostream>
using namespace std;

float pSuma(float a, float b);
float pResta(float a, float b);
float pMultiplicacion(float a, float b);
float pDivision(float a, float b);

float** crearMatriz();

float pSuma(float a, float b) {
	float res;
	__asm {
		fld a;
		fld b;
		fadd st(0), st(1);
		fstp res;
	}
	return res;
}


float pDivision(float a, float b) {
	float res;
	__asm {
		fld a;
		fld b;
		fdiv;
		fstp res;
	}
	return res;
}

float pMultiplicacion(float a, float b) {
	float res;
	__asm {
		fld a;
		fld b;
		fmul st(0), st(1);
		fstp res;
	}
	return res;
}

float pResta(float a,float b) {
	float res;
	__asm {
		fld b;
		fld a;
		fsub st(0), st(1);
		fstp res;
	}
	return res;

}

float** sumarMatrices(float** a, float** b) {
	__asm {
		mov eax, 0;
	inicioCicloExterno:
		mov ebx, 0;
	inicioCicloInterno:
		//suma

		inc ebx;
		cmp ebx, 4;
		jne inicioCicloInterno;
		inc eax;
		cmp eax, 4;
		jne inicioCicloExterno;

		//termina el ciclo
	}
}

float** crearMatriz() {
	const int tam = 4;
	
	float** matrix = 0;
	matrix = new float*[tam];
	for (size_t i = 0; i < tam; i++) {
		matrix[i] = new float[tam];
		cout << "Fila " << i << " ";
		for (size_t j = 0; j < tam; j++) {
			cout << "Columna " << j  << endl;
			cin >> matrix[i][j];
		}
	}
	return matrix;
}


int main() {
	const int n = 4;
	cout << "Ingrese la matriz A" << endl;
	float** A = crearMatriz();
	cout << "Ingrese la matriz B" << endl;
	float** B = crearMatriz();

	cout << "Que operacion desea realizar?" << endl;
	cout << " 1 Suma\n 2 Resta\n 3 Multiplicacion\n 4 Division" << endl;

	int operacion;
	cin >> operacion;

	__asm {
		mov eax, operacion;
		cmp eax, 1;
		je sumar;
		cmp eax, 2;
		je restar;
		cmp eax, 3;
		je multiplicar;
		cmp eax, 4;
		je dividir;

	sumar:

		mov eax, 0;
	inicioCicloExternoS:
		mov ebx, 0;
	inicioCicloInternoS:
		//suma

		inc ebx;
		cmp ebx, 4;
		jne inicioCicloInternoS;
		inc eax;
		cmp eax, 4;
		jne inicioCicloExternoS;

		//termina el ciclo
		jmp terminar;
	

	restar:
	
		mov eax, 0;
	inicioCicloExternoR:
		mov ebx, 0;
	inicioCicloInternoR:
		//suma

		inc ebx;
		cmp ebx, 4;
		jne inicioCicloInternoR;
		inc eax;
		cmp eax, 4;
		jne inicioCicloExternoR;

		//termina el ciclo
		jmp terminar;

	multiplicar:

		mov eax, 0;
	inicioCicloExternoM:
		mov ebx, 0;
	inicioCicloInternoM:
		//suma

		inc ebx;
		cmp ebx, 4;
		jne inicioCicloInternoM;
		inc eax;
		cmp eax, 4;
		jne inicioCicloExternoM;

		//termina el ciclo
		jmp terminar;

	dividir:

		mov eax, 0;
	inicioCicloExternoD:
		mov ebx, 0;
	inicioCicloInternoD:
		//suma

		inc ebx;
		cmp ebx, 4;
		jne inicioCicloInternoD;
		inc eax;
		cmp eax, 4;
		jne inicioCicloExternoD;

		//termina el ciclo
		jmp terminar;

	terminar:
	}

	//Imprimiendo la matriz
	for (size_t i = 0; i < n; i++){
		for (size_t j = 0; j < n; j++){
			cout << A[i][j] << ", ";
		}
		cout << endl;
	}
	
	//Limpiando la memoria
	for (size_t i = 0; i < n; i++) {
		delete[] A[i];
		delete[] B[i];
	}
	delete[] A;
	delete[] B;
	A = 0;
	B = 0;
	
	system("pause");
	return 0;
}