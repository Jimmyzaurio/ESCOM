#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int raster[1080][1920][3];

int aleatorio() { return rand()%255; }

void line(int x1, int y1, int x2, int y2) {
	double m = abs((y1 - y2)/(x1 - x2)); // Sacamos el valor absoluto para no que no intente guardar en una dirección negativa
	int y = y1;
	int x;
	for (x = x1; x <= x2; ++x) {
		y += m;
		raster[y][x][0] = 0;
		raster[y][x][1] = 0;
		raster[y][x][2] = 0;
	}
}

void paint() {
	printf("P3\n");
  	printf("1920 1080\n");
  	printf("255\n");
  	int i, j;
	for (i = 0; i < 1080; ++i)
		for (j = 0; j < 1920; ++j)
			printf(" %d %d %d ", raster[i][j][0], raster[i][j][1], raster[i][j][2]);
    printf("\n");
}

int main() {
	int x1, x2, y1, y2;
	srand(time(NULL));

	int i, j;
	for (i = 0; i < 1080; ++i) {
		for (j = 0; j < 1920; ++j) {
			raster[i][j][0] = 255;
			raster[i][j][1] = 255;
			raster[i][j][2] = 255;
		}
	}
	for (i = 0; i < 1000; ++i) {
		x1 = aleatorio()%1920;
		y1 = aleatorio()%1080;
		x2 = ((aleatorio()%1920) + x1 + 1)%1920;
		y2 = aleatorio()%1080;
		line(x1, y1, x2, y2);
	}
	paint();
	return 0;
}
