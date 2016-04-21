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


int main() {
	double res = pDivision(1.4, 0.5);
	cout << res << endl;
	system("pause");
	return 0;
}