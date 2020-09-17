#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv){
	double media_llegada, media_proceso;
	int numero_iteraciones, i, j;
	char* nombre_fichero;
	double* tabla_tiempos;
	FILE* pf;
	double tiempo_llegada, tiempo_proceso, tiempo_entrada, tiempo_salida, t;
	double Le, u, Wt, We, Lt;
	int n;

	if(argc < 2){
		printf("Error en los parametros de entrada\n");
		printf("\t./main fichero.csv\n");
		return -1;
	}

	nombre_fichero = argv[1];
	/*Abrimos el fichero*/
	pf = fopen(nombre_fichero, "w");

	/*Control de errores apertura fichero*/
	if(!pf){
		printf("Error en el fichero\n");
		return -1;
	}

	/*Guardamos tasa media de llegadas*/
	printf("\nIntroduce la tasa media de llegadas: ");
	scanf("%lf", &media_llegada);

	/*Guardamos la tasa media de proceso*/
	printf("\nIntroduce la tasa media de proceso: ");
	scanf("%lf", &media_proceso);

	/*Guardamos el numero de iteraciones*/
	printf("\nIntroduce el numero de iteraciones: ");
	scanf("%d", &numero_iteraciones);

	/*Reservamos memoria para la tabla en la que almacenaremos los tiempos de salida*/
	tabla_tiempos = (double*)malloc(numero_iteraciones * sizeof(double));
	tiempo_llegada = -log(drand48())/media_llegada;
	tiempo_proceso = -log(drand48())/media_proceso;
	tiempo_entrada = tiempo_llegada;
	tiempo_salida = tiempo_entrada + tiempo_proceso;
	
	/*Guardamos la primera salida*/
	n = 1;
	t = tiempo_proceso;
	tabla_tiempos[0] = tiempo_salida;
	Le = n;
	We = t;

	/*Realiazamos la primera impresion para los parametros del csv*/
	fprintf(pf, "Llegada_Acumulada;Tiempo_Servicio;Tiempo_Entrada;Tiempo_Salida;Elementos_Sistema;Tiempo_Sistema\n");
	fprintf(pf, "%lf;%lf;%lf;%lf;%d;%lf\n", tiempo_llegada, tiempo_proceso, tiempo_entrada, tiempo_salida, n, t);

	/*Comenzamos el bucle de iteraciones*/
	i = 1;
	j = 0;
	while(i < numero_iteraciones){
		tiempo_llegada = tiempo_llegada - log(drand48())/media_llegada;
		tiempo_proceso = -log(drand48())/media_proceso;
		n += 1;
		while((j < i) && (tiempo_llegada > tabla_tiempos[j])){
			n--;
			j++;
		}

		if(n < 2){
			tiempo_entrada = tiempo_llegada;
		}
		else{
			tiempo_entrada = tiempo_salida;
		}

		tiempo_salida = tiempo_entrada + tiempo_proceso;
		tabla_tiempos[i] = tiempo_salida;
		t = tiempo_salida - tiempo_llegada;

		Le += n;
		We += t;

		fprintf(pf, "%lf;%lf;%lf;%lf;%d;%lf\n", tiempo_llegada, tiempo_proceso, tiempo_entrada, tiempo_salida, n, t);

		i++;
	}

	/*Calculamos los parametros a imprimir por stderr*/
	u = media_llegada/media_proceso;
	Wt = 1/(media_proceso - media_llegada);
	We = We/i;
	Lt = media_llegada * Wt;
	Le = Le/i;
	fprintf(stderr, "%d La Intensidad de tráfico= T.M.llegada / T.M.proceso es: %lf\n",i, u);
	fprintf(stderr, "El tiempo medio de estancia en el sistema TEORICO (W) es: %lf\n", Wt);
	fprintf(stderr, "El calculo empirico de W como media de T es: %lf\n", We);
	fprintf(stderr, "El calculo teorico de la L mediante Little es: %lf\n", Lt);
	fprintf(stderr, "La L empirica es: %lf\n", Le);

	//cerramos el fichero y liberamos memoria
	fclose(pf);
	free(tabla_tiempos);
	
	return 0;
}