//guia https://msdn.microsoft.com/en-us/library/4ks26t93.aspx
//guia2 http://www.jegerlehner.ch/intel/IntelCodeTable_es.pdf no sirve para floats

#include <iostream>
using namespace std;

float A[4][4];
float B[4][4];
float C[4][4];

float pSuma(float a, float b);
float pResta(float a, float b);
float pMultiplicacion(float a, float b);
float pDivision(float a, float b);

void iniciarMatrices();

float pSuma(float a, float b) {
	float res;
	__asm {
		fld a;
		fld b;
		fadd st(0), st(1);
		fstp res;
		fstp st(0);
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
		fstp st(0);
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
		fstp st(0);
	}
	return res;
}

float pResta(float a,float b) {
	float res;
	__asm {
		fld a;
		fld b;
		fsub st(0), st(1);
		fstp res;
		fstp st(0);
	}
	return res;
}


void iniciarMatrices() {
	cout << "Ingrese la matriz A" << endl;
	for (size_t i = 0; i < 4; i++) {
		cout << "Fila " << i << " ";
		for (size_t j = 0; j < 4; j++) {
			cout << "Columna " << j << endl;
			cin >> A[i][j];
		}
	}

	cout << "Ingrese la matriz B" << endl;
	for (size_t i = 0; i < 4; i++) {
		cout << "Fila " << i << " ";
		for (size_t j = 0; j < 4; j++) {
			cout << "Columna " << j << endl;
			cin >> B[i][j];
		}
	}
}



int main() {
	const int n = 4;
	const int m = 16;
	int operacion;
	int p = 0;

	iniciarMatrices();

	cout << "Que operacion desea realizar?" << endl;
	cout << " 1 Suma\n 2 Resta\n 3 Multiplicacion\n 4 Division" << endl;

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

		mov ecx, 0
	inicioCicloS:
		mov eax, A[ecx * type float];
		push eax;
		mov eax, B[ecx * type float];
		push eax;
		call pSuma;
		mov ecx, p
		fstp C[ecx * type float];
		pop eax;
		pop eax;
		
		inc p;
		cmp ecx, m;
		jne inicioCicloS;
		jmp terminar;
		
	restar:

		mov ecx, 0
	inicioCicloR:
		mov eax, A[ecx * type float];
		push eax;
		mov eax, B[ecx * type float];
		push eax;
		call pResta;
		mov ecx, p
		fstp C[ecx * type float];
		pop eax;
		pop eax;

		inc p;
		cmp ecx, m;
		jne inicioCicloR;
		jmp terminar;

	multiplicar:

		mov ecx, 0
	inicioCicloM:
		mov eax, A[ecx * type float];
		push eax;
		mov eax, B[ecx * type float];
		push eax;
		mov ecx, p
		fstp C[ecx * type float];
		pop eax;
		pop eax;

		inc p;
		cmp ecx, m;
		jne inicioCicloM;
		jmp terminar;

	dividir:

		mov ecx, 0
	inicioCicloD:
		mov eax, A[ecx * type float];
		push eax;
		mov eax, B[ecx * type float];
		push eax;
		call pDivision;
		mov ecx, p
		fstp C[ecx * type float];
		pop eax;
		pop eax;

		inc p;
		cmp ecx, m;
		jne inicioCicloD;
		jmp terminar;

	terminar:
	}
	
	//Imprimiendo la matriz
	for (size_t i = 0; i < n; i++){
		for (size_t j = 0; j < n; j++){
			cout << C[i][j] << ", ";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}