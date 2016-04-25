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
	int contadorE;
	int contadorI;
	__asm {
		mov ecx, 4;
		mov contadorE, 0;
	inicioCicloExterno:
		mov contadorI, 0;
	inicioCicloInterno:
		//suma

		inc contadorI;
		cmp contadorI, ecx;
		jne inicioCicloInterno;
		jmp inicioCicloExterno;
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
	}
	cout << "Se va a sumar" << endl;
	goto terminar;
	__asm {
	restar:
	}
	cout << "Se va a restar" << endl;
	goto terminar;
	__asm {
	multiplicar:
	}
	cout << "se va a multiplicar" << endl;
	goto terminar;
	__asm {
	dividir:
	}
	cout << "Se va a dividir" << endl;	

terminar:
	cout << "Borrando memoria" << endl;
	
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