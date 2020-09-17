#include <stdio.h>
#include <pgm.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

  gray maxval;
  int cols;
  int rows;

  FILE *inputf = fopen("foto.pgm", "r");
  FILE *outputf = fopen("foto_rotada.pgm", "w");

  //gray **pgm_readpgm(FILE*fp, int *cols, int *rows, gray *maxval);
  gray **imagen = pgm_readpgm(inputf, &cols, &rows, &maxval);

  fprintf(outputf, "P2 \n# Esto es un comentario \n%d %d \n%d\n", rows, cols, maxval);

  int i, j, matriz[cols][rows];

  for(j = 0; j<cols; ++j){
    for(i = 0; i<rows; ++i){
      matriz[j][i] = imagen[rows-1-i][j];
    }
  }

  for(j = 0; j < cols; ++j){
    for(i = 0; i < rows; ++i){
      fprintf(outputf, " %d", matriz[j][i]);
    }
    fprintf(outputf, "\n");
  }

  fclose(inputf);
  fclose(outputf);
  return 0;
}
