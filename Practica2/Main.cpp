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
void imprimirMatriz(float M[4][4]);
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
	int zero = 0;
	__asm {
		fld b;
		fld a; 
		mov eax, a;
		cmp eax, 0;
		je Error;
		fdiv;
		fstp res;
		fstp st(0);
		jmp Bueno;
	Error:
	}
	//exit(-1);
	cout << "Error. Division por cero, reinicie las matrices" << endl;
	iniciarMatrices();
	__asm {
		//jmp MenuPrincipal;
	Bueno:
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

void imprimirMatriz(float M[4][4]) {
	int n = 4;

	for (size_t i = 0; i < n; i++) {
		for (size_t j = 0; j < n; j++) {
			cout << M[i][j] << "\t ";
		}
		cout << endl;
	}

}



int main() {
	const int n = 4;
	const int m = 16;
	int p = 0;
	int operacion;
	cout << "Inicie Las Matrices" << endl;
	iniciarMatrices();
	__asm {
	MenuPrincipal:
	}

	cout << "Que operacion desea realizar?" << endl;
	cout << " -1 Suma\n -2 Resta\n -3 Multiplicacion\n -4 Division\n -5 Mostrar Matriz A\n -6 Mostrar Matriz B\n -7 Mostrar Matriz Resultante\n -8 Reiniciar Matrices\n -9 Cerrar el programa" << endl;
	cin >> operacion;
	__asm{
	
		mov eax, operacion;
		cmp eax, 1;
		je menuSuma;
		cmp eax, 2;
		je menuResta;
		cmp eax, 3;
		je menuMultiplicar;
		cmp eax, 4;
		je menuDividir;
		cmp eax, 5;
		je MostrarA;
		cmp eax, 6;
		je MostrarB;
		cmp eax, 7;
		je MostrarC;
		cmp eax, 8;
		je reiniciarM;
		cmp eax, 9;
		je salir;
		jmp ErrorLectura;

	MostrarA:
	}
	cout << "Matriz A" << endl;
	imprimirMatriz(A);


	__asm {
		jmp MenuPrincipal;
	MostrarB:
	}
	cout << "Matriz B" << endl;
	imprimirMatriz(B);

	__asm {
		jmp MenuPrincipal;
	MostrarC:
	}
	cout << "Matriz Resultado" << endl;
	imprimirMatriz(C);
	__asm {
		jmp MenuPrincipal;
	reiniciarM:
	}
	iniciarMatrices();

	__asm{
		jmp MenuPrincipal;
	menuSuma:
		
	}
	cout << " -1 Realizar Operacion\n -2 Cancelar" << endl;
	cin >> operacion;
	__asm {
		mov eax, operacion;
		cmp eax, 1;
		je sumar;
		cmp eax, 2;
		je MenuPrincipal;
		jmp ErrorLectura;

	}

	__asm {

	menuResta:

	}

	cout << " -1 Realizar Operacion\n -2 Cancelar" << endl;
	cin >> operacion;

	__asm {
		mov eax, operacion;
		cmp eax, 1;
		je restar;
		cmp eax, 2;
		je restar;
		jmp ErrorLectura;

	menuMultiplicar:
	}
	cout << " -1 Realizar Operacion\n -2 Cancelar" << endl;
	cin >> operacion;

	__asm {

		mov eax, operacion;
		cmp eax, 1;
		je multiplicar;
		cmp eax, 2;
		je MenuPrincipal;
		jmp ErrorLectura;


	menuDividir:

	}
	cout << " -1 Realizar Operacion\n -2 Cancelar" << endl;
	cin >> operacion;

	__asm {

		mov eax, operacion;
		cmp eax, 1;
		je dividir;
		cmp eax, 2;
		je MenuPrincipal;
		jmp ErrorLectura;

	sumar:

		mov ecx, 0
			inicioCicloS :
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
		mov p, 0;
		jmp terminar;

	restar:

		mov ecx, 0
			inicioCicloR :
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
		mov p, 0;
		jmp terminar;

	multiplicar:

		mov ecx, 0
	inicioCicloM:
		mov eax, A[ecx * type float];
		push eax;
		mov eax, B[ecx * type float];
		push eax;
		call pMultiplicacion;
		mov ecx, p
		fstp C[ecx * type float];
		pop eax;
		pop eax;

		inc p;
		cmp ecx, m;
		jne inicioCicloM;
		mov p, 0;
		jmp terminar;

	dividir:

		mov ecx, 0
			inicioCicloD :
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
		mov p, 0;
		jmp terminar;

	ErrorLectura:
	}
	cout << "Error, no se reconoce" << endl;
	cin.clear();
	cin.ignore(1);
	__asm{
	terminar:
		jmp MenuPrincipal;
	salir:
	}
	
	return 0;
}



