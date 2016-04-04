#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int aleatorio() {
  return rand()
%256;
}

int raster[1080][1920][3];

int main() {
  srand(time(NULL));
  printf("P3\n");
  printf("1920 1080\n");
  printf("255\n");
  for (int i = 0; i < 1080; ++i) {
    for (int j = 0; j < 1920; ++j) {
      raster[i][j][0] = aleatorio();
      raster[i][j][1] = aleatorio();
      raster[i][j][2] = aleatorio();
    }
  }

    printf("\n");

  for (int i = 0; i < 1080; ++i)
    for (int j = 0; j < 1920; ++j)
      printf(" %d %d %d ", raster[i][j][0], raster[i][j][1], raster[i][j][2]);
    printf("\n");

  return 0;
}
