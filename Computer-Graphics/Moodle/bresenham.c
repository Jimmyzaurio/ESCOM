#include "bresenham.h"

int raster[ROWS][COLUMNS][3];

void bres(Coord p1, Coord p2, unsigned int color[3]) {
	int dx, dy, i, e;
	int incx, incy, inc1, inc2;
	int x,y;
	int x1 = p1.x;
	int y1 = p1.y;
	int x2 = p2.x;
	int y2 = p2.y;

	dx = x2 - x1;
	dy = y2 - y1;

	if (dx < 0) dx = -dx;
	if (dy < 0) dy = -dy;

	incx = 1;

	if (x2 < x1) incx = -1;

	incy = 1;
	
	if (y2 < y1) incy = -1;
	x=x1;
	y=y1;

	if (dx > dy) {
		put_pixel(x, y, color);
		e = 2 * dy - dx;
		inc1 = 2 * (dy - dx);
		inc2 = 2 * dy;
		for(i = 0; i < dx; ++i) {
			if(e >= 0) {
				y += incy;
				e += inc1;
			}
			else 
				e += inc2;
			x += incx;
			put_pixel(x, y, color);
		}
	} else {
		put_pixel(x, y, color);
		e = 2 * dx - dy;
		inc1 = 2 * (dx - dy);
		inc2 = 2 * dx;
		for(i = 0; i < dy; i++) {
			if(e >= 0) {
				x += incx;
				e += inc1;
			}
			else 
				e += inc2;
			y += incy;
			put_pixel(x, y, color);
		}
	}
}

void put_pixel(int x, int y, unsigned int color[3]) {
	raster[x][y][0] = color[0];
	raster[x][y][1] = color[1];
	raster[x][y][2] = color[2];
}

void paint() {
  	FILE *archivo = fopen("cubo.ppm", "w");
  	int i, j;

	fprintf(archivo, "P3\n");
  	fprintf(archivo, "%d %d\n", COLUMNS, ROWS);
  	fprintf(archivo, "255\n");
	for (i = 0; i < 1080; ++i)
		for (j = 0; j < 1920; ++j)
			fprintf(archivo, " %d %d %d ", raster[i][j][0], raster[i][j][1], raster[i][j][2]);
    fprintf(archivo, "\n");
}

void clean() {
	int i, j;
	for (i = 0; i < 1080; ++i)
		for (j = 0; j < 1920; ++j)
			raster[i][j][0] = raster[i][j][1] = raster[i][j][2] = 255;
}

Coord ProyectaPunto(Coord p, double dist) {
	double factor = dist/p.z;
	Coord r;
	r.x = p.x * factor;
	r.y = p.y * factor;
	r.z = dist;
	return r;
}