#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ppm.h>

pixel** imagen_color(pixel** imagen, int nrows, int ncols, int maxval, char* color){
	int i;
	int j;
	pixel** salida;

	salida = ppm_allocarray(ncols, nrows);

	for(i = 0; i < nrows; i++){
		for(j = 0; j < ncols; j++){
			salida[i][j] = ppm_parsecolor(color, PPM_GETB(imagen[i][j]));
		}
	}
	return salida;
}

int main(int argc, char** argv){
	char* nombre_original;
	char* nombre_salida;
	char* color;
	pixel** imagen_original;
	pixel** imagen_salida;
	int rows;
	int cols;
	pixval maxVal;
	FILE* fichero;

	if(argc < 4){
		printf("Error en los parametros\n");
		return -1;
	}

	nombre_original = argv[1];
	nombre_salida = argv[3];
	color = argv[2];

	fichero = fopen(nombre_original, "r");

	if(fichero == NULL){
		printf("Error al leer la imagen\n");
		return -1;
	}

	imagen_original = ppm_readppm(fichero, &cols, &rows, &maxVal);

	if(strcmp(color, "rojo") == 0){
		imagen_salida = imagen_color(imagen_original, rows, cols, maxVal, "red");
		fclose(fichero);
		// Escribimos en el fichero
		fichero = fopen(nombre_salida, "w");
		ppm_writeppm(fichero, imagen_salida, cols, rows, maxVal, PPM_FORMAT);
	} 
	else if(strcmp(color, "azul") == 0){
		imagen_salida = imagen_color(imagen_original, rows, cols, maxVal, "blue");
		fclose(fichero);
		// Escribimos en el fichero
		fichero = fopen(nombre_salida, "w");
		ppm_writeppm(fichero, imagen_salida, cols, rows, maxVal, PPM_FORMAT);
	}else if(strcmp(color, "verde") == 0){
		imagen_salida = imagen_color(imagen_original, rows, cols, maxVal, "green");
		fclose(fichero);
		// Escribimos en el fichero
		fichero = fopen(nombre_salida, "w");
		ppm_writeppm(fichero, imagen_salida, cols, rows, maxVal, PPM_FORMAT);
	}
	else{
		printf("Color incorrecto\n");
		return -1;
	}

	ppm_freearray(imagen_salida, rows);
	fclose(fichero);

	return 0;
}	