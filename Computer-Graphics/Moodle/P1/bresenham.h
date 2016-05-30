#ifndef BRESENHAM
#define BRESENHAM

#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 1920
#define ROWS 1080

typedef struct coord{
	double x;
	double y;
	double z;
}Coord;

void bres(Coord p1, Coord p2, unsigned int color[3]);
void put_pixel(int x, int y, unsigned int color[3]);
void paint();
void clean();
Coord ProyectaPunto(Coord p, double dist);

#endif