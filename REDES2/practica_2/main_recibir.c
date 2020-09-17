#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "nivelEth.h"
#include <stdint.h>
#include <sys/time.h>
#include <signal.h>

int parar=0;
char canal[20]={0};
struct timeval currentTime;
int count;
char flag[3] = "he";

void fn_signal(int nsignal){
	int finalizar = FinalizarEth();
	if(strcmp(flag, "-r") == 0){
		printf("Numero de tramas capturadas: %d\n", count);
	}

	
	if (finalizar == - 1){
		printf("Error finalizando\n");
		exit(1);
	}
	
	
	else{
		printf("Finalizacion correcta\n");
		exit(0);
	}
	
	parar = 1;
}

// Funcion de recepcion de mensajes. Esta funcion debe  llamada cada vez que se recibe un mensaje
// remitente: Direccion Eth remitente
// tamano: Tamaño del mensaje formato practica
// mensaje : Buffer  mensaje
// tipo: Tipo ethernet de mensaje
// tv: Informacion de captura de la trama
int notificacion (const uint8_t *remitente,int tamano,const uint8_t *mensaje, uint16_t tipo,  const struct timeval *tv )

{
	// Funcion de recepcion de Tramas
	/**PRACTICA Implementar aquí las acciones necesarias al recibir un mensaje*/
	char usuario[20] = {0}, canal_origen[20] = {0}, fecha[20] = {0};
	uint16_t tam;
	char cadena[1456] = {0};

	if(!remitente || !mensaje)
		return -1;

	//Guardamos la fecha de envio
	memcpy(fecha, mensaje, 20);

	//Guardamos el canal
	memcpy(canal_origen, mensaje + 20, 20);
	

	//Comprobamos el canal
	if(strncmp(canal, canal_origen, 20) != 0){
		//Si no se corresponde con el nuestro salimos
		printf("El canal no coincide\n");
		return -1;
	}

	//Si el canal se corresponde guardamos el nombre del usuario que envia el mensaje
	memcpy(usuario, mensaje + 20 * 2, 20);


	//Impresion del mensaje recibido
	printf("Mensaje de: %s\n", usuario);
	printf("Mac origen: %x-%x-%x-%x-%x-%x\n", remitente[0], remitente[1], remitente[2], remitente[3], remitente[4], remitente[5]);
	memcpy(&tam, mensaje + 20 * 3, sizeof(uint16_t));
	memcpy(cadena, mensaje + 20 * 3 + sizeof(uint16_t), tam);
	printf("Mensaje recibido: \n%s\n", cadena);
	printf("El mensaje fue enviado en la fecha siguiente -> %s\n", fecha);
	printf("Recibido en Secs:%ld (tiempo desde inicio)\n",((tv->tv_sec)-(currentTime.tv_sec)));
	count++;

	return ETH_OK;
}




int main (int argc,char *argv[]){
	//recibir	
	int resultado;
	int timeout=1000;
	int finalizado;
	uint16_t tipos[2];

	if(argc == 2 && strcmp(argv[1],"-h") == 0){
		printf("Ayuda\n");
		printf("Para los ejercicios 1 y 2 ejecutar como-> ./recibir -n canal\n");
		printf("Para el ejercicio 3 ejecutar como-> ./recibir -r canal\n");
		printf("Para ayuda-> ./recibir -h\n");
		return -1;
	}

	if(argc != 3){
	    printf("Error en el numero de parametros\n./recibir -h para ayuda\n");
		return -1;
	}

	//Guardamos el tiempo en el que empezamos a capturar
	gettimeofday(&currentTime,NULL);
		
	strcpy(canal,argv[2]);      
    //INICIALIZAMOS EL NIVEL Ethernet
    
    tipos[0] = TYPE1;
    tipos[1] = TYPE2;
	resultado = InicializarEth(tipos, 2,notificacion,timeout);
	count = 0;
	
	
	if (resultado==-1){
		printf("Error inicializando Ethernet\n");
		return -1;
	}
	
	if(strcmp(argv[1], "-n") == 0 || strcmp(argv[1], "-r") == 0){
		// Guardamos el valor del argumento en variable global para leerlo correctamente despues
		strcpy(flag, argv[1]);		
		signal(SIGINT,fn_signal);
	
		while(parar == 0){
			/* Bucle infinito NO Modificar  */
		}
	}
	else{
		printf("Error en los argumentos del programa\n");
	}
    
	finalizado = FinalizarEth();

	if (finalizado == - 1){
		printf("Error finalizando\n");
		return (EXIT_FAILURE);
	}
	else{
		printf("Finalizacion correcta\n");
		return (EXIT_SUCCESS);
	}
}
