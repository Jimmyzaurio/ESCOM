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
	double angle = 180.0/u;
	int conta = 0;
	
	int i;
	double x = R;
	double y = 0;
	double z = 0;

	for (i = 0; i < v; i++) {		
		double x1 = x;
		double y1 = y;
		int j;
		for (j = 0; j < u; j++) {
			//double z = x * sen(M_PI*angle/180.0);
			double x1_ = x1;
			double y1_ = y1;
			x1 = x1_ * cos(M_PI*angle/180.0) - y1_ * sin(M_PI*angle/180.0);
			y1 = x1_ * sin(M_PI*angle/180.0) + y1_ * cos(M_PI*angle/180.0);
			printf("%d \t %.4lf \t %.4lf \t %.4lf r = %lf\n", conta, x1, y1, z, sqrt(x1*x1 + y1*y1 + z*z));
			conta++;
		}
		x1 = x;
		y1 = y;
		x = x1 * cos(M_PI*angle/180.0) - y1 * sin(M_PI*angle/180.0);
		y = x1 * sin(M_PI*angle/180.0) + y1 * cos(M_PI*angle/180.0);
	}
	/*
	int i;
	for (i = 0; i < v; i++) {
		double x = R;
		double y = 0;
		double x1 = x;
		double y1 = y;
		double z = x * sin(M_PI*angle/180.0);
		int j;
		for (j = 0; j < u; j++) {
			//double z = x * sen(M_PI*angle/180.0);
			double x1_ = x1;
			double y1_ = y1;
			x1 = x1_ * cos(M_PI*angle/180.0) - y1_ * sin(M_PI*angle/180.0);
			y1 = x1_ * sin(M_PI*angle/180.0) + y1_ * cos(M_PI*angle/180.0);
			printf("%d \t %.4lf \t %.4lf \t %.4lf r = %lf\n", conta, x1, y1, z, sqrt(x1*x1 + y1*y1 + z*z));
			conta++;
		}
		x1 = x;
		y1 = y;
		x = x1 * cos(M_PI*angle/180.0) - y1 * sin(M_PI*angle/180.0);
		y = x1 * sin(M_PI*angle/180.0) + y1 * cos(M_PI*angle/180.0);
	}
	*/
	return 0;
}