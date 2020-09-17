#include <stdio.h>
#include <pgm.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

  gray maxval;
  int cols;
  int rows;
  int i, j;

  gray **imagen;
  gray **matriz;

  while(1){

  FILE *inputf = fopen("foto.pgm", "r");

  //gray **pgm_readpgm(FILE*fp, int *cols, int *rows, gray *maxval);
  imagen = pgm_readpgm(inputf, &cols, &rows, &maxval);
  //gray **pgm_allocarray(int cols, int rows); (sirve para la gestion de memoria asignando una escala de grises)
  matriz = pgm_allocarray(rows, cols);

  for(i = 0; i<cols; ++i){
    for(j = 0; j<rows; ++j){
      matriz[i][j] = imagen[rows-1-j][i];
    }
  }

  FILE *outputf = fopen("foto.pgm", "w");
  //void pgm_writepgm(FILE *fp, gray** grays, int cols, int rows, gray maxval, int forceplain); (escribe el encabezado y todos los datos para una imagen PGM)
  pgm_writepgm(outputf, matriz, rows, cols, maxval, PGM_FORMAT);
  //void pgm_freearray(gray **grays, int rows); (libera la matriz asignada con pgm_allocarray que contiene el numero dado de filas)
  pgm_freearray(matriz, cols);

  fclose(outputf);

  sleep(1);
  }
}
