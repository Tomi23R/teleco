#include <stdio.h>
#include <pgm.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(){

  int cols;
  int rows;
  gray maxval;

  FILE *inputf = fopen("foto.pgm", "r");
  //gray **pgm_readpgm(FILE*fp, int *cols, int *rows, gray *maxval);
  gray **imagen= pgm_readpgm(inputf, &cols, &rows, &maxval);
  fclose(inputf);

  FILE *outputf = fopen("foto_espejo.pgm", "w");

  fprintf(outputf, "P2 \n# Esto es un comentario \n%d %d \n%d\n", cols, rows, maxval);

  int i, j;
  //int matriz[rows][cols];

  for(i = 0; i < rows; ++i){
    for(j = cols-1; j >= 0; --j){
      fprintf(outputf, " %d", imagen[i][j]);
    }
    fprintf(outputf, "\n");
  }

  /*for(i = 0; i < cols; ++i){
    for(j = 0; j < rows; ++j){
      fprintf(outputf, " %d", matriz[i][j]);
    }
    fprintf(outputf, "\n");
  }*/

  pgm_freearray(imagen, rows);


  fclose(outputf);

  return 0;
}
