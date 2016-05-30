// Author: Jesus Saucedo Perez
#include "bresenham.h"
#include "vertex.h"

#define MAX 1000000.0

int main() {
	FILE *fp = NULL;
	char buf[10000];
	const double DISTANCE = 100.0;
	const double EYES = 7.0;

	fp = fopen("cubo.raw", "r");

	if (fp == NULL)
		perror("Can't open file\n");

	Node *data = NULL;
	unsigned int rojo[] = {255, 0, 0};
	unsigned int azul[] = {0, 0, 255};
	double x_min = MAX;
	double y_min = MAX;
	double z_min = MAX;
	rewind(fp); //Sets the position indicator associated with stream to the beginning of the file.
	clean();

	while (fgets(buf, sizeof buf, fp) != NULL) {
		Coord p1, p2, p3;
		fscanf(fp, "%lf %lf %lf", &p1.x, &p1.y, &p1.z);
		fscanf(fp, "%lf %lf %lf", &p2.x, &p2.y, &p2.z);
		fscanf(fp, "%lf %lf %lf", &p3.x, &p3.y, &p3.z);
		data = insert(data, p1);
		data = insert(data, p2);
		data = insert(data, p3);

		if (x_min > p1.x) x_min = p1.x;
		if (x_min > p2.x) x_min = p2.x;
		if (x_min > p3.x) x_min = p3.x;

		if (y_min > p1.y) y_min = p1.y;
		if (y_min > p2.y) y_min = p2.y;
		if (y_min > p3.y) y_min = p3.y;

		if (z_min > p1.z) z_min = p1.z;
		if (z_min > p2.z) z_min = p2.z;
		if (z_min > p3.z) z_min = p3.z;
	}

	if (x_min < 0.0) x_min = -x_min;	
	if (y_min < 0.0) y_min = -y_min;
	if (z_min < 0.0) z_min = -z_min;

	if (x_min > 0.0) x_min = 0.0;
	if (y_min > 0.0) y_min = 0.0;
	if (z_min > 0.0) z_min = 0.0;

	Node *aux = data;
	while (aux != NULL) {
		Coord p1, p2, p3;
		Coord p4, p5, p6;

		p1 = aux -> p;
		p1.x += x_min * DISTANCE;
		p1.y += y_min * DISTANCE;
		p1.z += z_min * DISTANCE;

		aux = aux -> next;
		p2 = aux -> p;
		p2.x += x_min * DISTANCE;
		p2.y += y_min * DISTANCE;
		p2.z += z_min * DISTANCE;

		aux = aux -> next;
		p3 = aux -> p;
		p3.x += x_min * DISTANCE;
		p3.y += y_min * DISTANCE;
		p3.z += z_min * DISTANCE;

		p4 = p1;
		p4.y += EYES;

		p5 = p2;
		p5.y += EYES;

		p6 = p3;
		p6.y += EYES;

		aux = aux -> next;

		Coord a = ProyectaPunto(p1, DISTANCE);
		Coord b = ProyectaPunto(p2, DISTANCE);
		Coord c = ProyectaPunto(p3, DISTANCE);
		Coord d = ProyectaPunto(p4, DISTANCE);
		Coord e = ProyectaPunto(p5, DISTANCE);
		Coord f = ProyectaPunto(p6, DISTANCE);

		/*
		printf("%lf %lf %lf\n", a.x, a.y, a.z);
		printf("%lf %lf %lf\n", b.x, b.y, b.z);
		printf("%lf %lf %lf\n", c.x, c.y, c.z);
		*/
		bres(a, b, rojo);
		bres(a, c, rojo);
		bres(b, c, rojo);

		bres(d, e, azul);
		bres(d, f, azul);
		bres(e, f, azul);
	}
	fclose(fp);	
	paint();
	return 0;
}