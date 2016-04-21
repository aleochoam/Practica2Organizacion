//guia https://msdn.microsoft.com/en-us/library/4ks26t93.aspx

#include <iostream>
using namespace std;

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
	__asm {
		cmp b, 0;
		je error;
		fld a;
	error:
		;
	}
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
		fld a;
		fld b;
		fsub st(0), st(1);
		fstp res;
	}
	return res;

}


int main() {
	double res = pMultiplicacion(5.0, 3.0);
	cout << res << endl;
	system("pause");
	return 0;
}