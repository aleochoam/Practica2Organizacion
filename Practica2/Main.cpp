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
	float** a = crearMatriz();
	
	for (size_t i = 0; i < n; i++){
		for (size_t j = 0; j < n; j++) {
			cout << a[i][j] << ", ";
		}
		cout << endl;
	}

	system("pause");
	return 0;
}