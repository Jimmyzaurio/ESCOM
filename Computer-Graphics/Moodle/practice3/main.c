/*
Autor: Jesus Saucedo Perez
Subject: Computer Graphics
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int validation(int u, int v) {
	if (u >= 3 && v >= 2) return 1;
	return 0;
}

/*
typedef struct Vertex{
	double x;
	double y;
	double z;
};

Vertex rotar(Vertex a, double angle) {
	a.x = a.x * cos(angle) - a.y * sin(angle);
	a.y = a.x * sin(angle) + a.y * cos(angle);
	return a;
}
*/

int main(int argc, char* argv[]) {
	if (argc != 3) {
		fprintf(stderr, "Must pass two arguments!\n");
		exit(1);
	}

	int u = atoi(argv[1]); // Sides of the polygon
	int v = atoi(argv[2]);

	// We're going to validate that it's possible to build that sphere
	if (!validation(u, v)) {
		printf("It is impossible to build a sphere with that parameters\n");
		exit(1);
	}

	double R = 10.0;
	
	/* Upper pyramid */
	double angle = 360.0/u;
	double r = 2*R/v;
	int j = 1;
	int conta = 0;

	printf("List vertex columns\n");
	printf("index \t %8s\t %8s\t %8s\n", "x", "y", "z");
	printf ("%d \t %.4lf \t %.4lf \t %.4lf\n", conta, 0.0, 0.0, R);

	for (; j < v/2; j++) {
		double x = r;
		double y = 0;
		double z = R - (j + 1)*(R/v);
		for (int i = 0; i < u; i++) {
			printf ("%d \t %.4lf \t %.4lf \t %.4lf\n %lf\n", conta, x, y, z, sqrt(x*x + y*y + z*z));
			x = x * cos(M_PI*angle/180.0) - y * sin(M_PI*angle/180.0);
			y = x * sin(M_PI*angle/180.0) + y * cos(M_PI*angle/180.0);
			conta++;
		}
		r += R/v;
	}

	r -= R/v;
	printf("%d --- \n", j);
	for (; j >= 0; j--) {
		double x = r;
		double y = 0;
		double z = -(v/2 - j)*(R/v);
		for (int i = 0; i < u; i++) {
			printf ("%d \t %.4lf \t %.4lf \t %.4lf  %lf\n", conta, x, y, z, sqrt(x*x + y*y + z*z));
			x = x * cos(M_PI*angle/180.0) - y * sin(M_PI*angle/180.0);
			y = x * sin(M_PI*angle/180.0) + y * cos(M_PI*angle/180.0);
			conta++;
		}
		r -= R/v;
	}
	printf ("%d \t %.4lf \t %.4lf \t %.4lf\n", conta, 0.0, 0.0, -R);
	return 0;
}