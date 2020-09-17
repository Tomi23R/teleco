#include <stdio.h>
#define FILAS 7
#define COLUMNAS 24
#define MAXVAL 15

FILE *f;

int main() {

  int matriz[FILAS][COLUMNAS]={
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    {0, 3, 3, 3, 3, 0, 0, 7, 7, 7, 7, 0, 0, 11, 11, 11, 11, 0, 0, 15, 15, 15, 15, 0},
    {0, 3, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 15, 0, 0, 15, 0},
    {0, 3, 3, 3, 0, 0, 0, 7, 7, 7, 0, 0, 0, 11, 11, 11, 0, 0, 0, 15, 15, 15, 15, 0},
		{0, 3, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0},
		{0, 3, 0, 0, 0, 0, 0, 7, 7, 7, 7, 0, 0, 11, 11, 11, 11, 0, 0, 15, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    f = fopen("foto.pgm", "w");

    fprintf(f, "P2 \n# Esto es un comentario \n%d %d \n%d\n", COLUMNAS, FILAS, MAXVAL);

    for(int i = 0; i < FILAS; i++){
      for(int j = 0; j < COLUMNAS; j++){
        fprintf(f, " %d", matriz[i][j]);
      }
      fprintf(f, "\n");
    }
    fclose(f);
  return 0;
}
