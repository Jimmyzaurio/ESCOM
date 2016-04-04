// Author: Saucedo Pérez Jesús
// Computer Graphics
// 3CM11
#include <stdio.h>
#include <stdlib.h>

void m1(double A[4][4], double B[4][4]) {
	double aux = 0.0;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			aux = 0.0;
			for (int k = 0; k < 4; k++) {
				aux += A[i][k]*B[k][j];
			}
			printf("%5.1lf ", aux);
		}
		printf("\n");
	}
}

double* m2(double A[4][4], double B[4][4]) {
	double* C;
	double aux;
	int conta = 0;
	C = (double*)malloc(16*sizeof(double));

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			aux = 0.0;
			for (int k = 0; k < 4; k++) {
				aux += A[i][k]*B[k][j];
			}
			*(C+conta++) = aux;
		}
	}	
	return C;
}

double* m3(double* A, double* B) {
	int conta = 0;
	double aux;
	double* C = NULL;
	C = (double*) malloc (sizeof (double) * 16);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			aux = 0.0;
			for (int k = 0; k < 4; k++) {
				aux += *(A + 4*i + k) * *(B + 4*k + j);
			}
			*(C + conta++) = aux;
		}
	}
	return C;
}

void print(double* C) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			printf("%5.1lf ", *(C++));
		}
		printf("\n");
	}
}

int main() {			
	double A[4][4], B[4][4];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			A[i][j] = i*4 + j + 1;
		}
	}
	B[0][0] = B[1][1] = B[2][2] = B[3][3] = 1;

	m1(A,B);
	print(m2(A,B)); 
	
	double *C = NULL;
	double *D = NULL;
	C = (double*) malloc (sizeof(double) * 16);
	D = (double*) malloc (sizeof(double) * 16);

	for (int i = 0; i < 16; i++)
		*(C + i) = i + 1;

	D[0] = D[5] = D[10] = D[15] = 1;
	print(m3(C,D));

	return 0;
}
