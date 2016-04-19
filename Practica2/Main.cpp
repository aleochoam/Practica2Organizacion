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

int main() {
	double res = pSuma(3.4, 0.6);
	cout << res << endl;
	system("pause");
	return 0;
}