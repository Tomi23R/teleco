#include "nivelEth.h"
#include "rc_funcs.h"
#include <stdio.h>
#include <pcap.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <pthread.h>
#include <signal.h>
#include <time.h>

void fn_signal(int nsignal){
	int finalizar = FinalizarEth();
	
	if (finalizar == - 1){
		printf("Error finalizando\n");
		exit(1);
	}
	else{
		printf("Finalizacion correcta\n");
		exit(0);
	}
}

// main para la función enviar
int main(int argc,char *argv[]){
   	char canal[20]={0}; 
   	char usuario[20]={0};
   	char fecha[20];
   	time_t t = time(NULL);
	struct tm tm = *localtime(&t);

	// Declaracion de Variables
	int resultado;
	uint16_t tipos[2];

	int finalizar;
	int enviado;
	uint8_t macdestino[6]={0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

	int timeout = 1000;
	char cadena[1456];//revisar para no exceder limite
	
	
	uint8_t trama_chat[1498]={0x00};	
    uint16_t incremento=0;
    int r;
    int i;
	
	uint16_t longitud_camposiguiente;

	if(argc == 2 && strcmp(argv[1],"-h") == 0){
		printf("Mensaje de ayuda\n");
		printf("Para los ejercicios 1 y 2 ejecutar como-> ./enviar -m canal usuario\n");
		printf("Para el ejercicio 3 ejecutar como-> ./enviar -a canal usuario\n");
		return -1;
	}
	
    //Comprobacion del numero de argumentos pasado por la linea de comandos
	if(argc!=4){
        printf("Error en el numero de parametros\n ./enviar -h para ayuda\n");
		return -1;
    }
                    
    tipos[0]=TYPE1;
    tipos[1]=TYPE2;
	resultado=InicializarEth(tipos,2,0,timeout);
	
	if (resultado==-1)
	{       
        printf("Error al IniciarNivel eTH, resultado = %d \n",resultado);
		return -1;
	}	
	else{    

    	memcpy(canal,argv[2],strlen(argv[2]));
	
        if (strlen(argv[2])>20){
			printf("El nombre del canal excede de la longitud permitida\n");
			return -1;
        }
		else if(strlen(argv[2])==0){
            printf("No se le ha pasado nada al nombre del canal\n");
			return -1;
        }
	
        memcpy(usuario,argv[3],strlen(argv[3]));
	

        if (strlen(argv[2])>20){
			printf("El nombre del canal excede de la longitud permitida\n");
			return -1;
       	}

	    else if(strlen(usuario)==0){
            printf("No se le ha pasado nada al nombre de usuario\n");
            return -1;
	    }
       
       	if(strcmp(argv[1],"-m") == 0){
       		/*Envio manual de mensajes*/
       		printf("Programa inciado para envio manual de mensajes\n");
       		//Para salir del bucle pulsar Ctrl+C
			signal(SIGINT,fn_signal);
				
			while (1){
				//Utilizamos bzero para limpiar la cadena
				bzero(cadena, 1456);
				//Pedimos por pantalla el mensaje
				printf ("\nIntroduce Mensaje a enviar: ");	
				fgets(cadena,1456,stdin);
				
				longitud_camposiguiente=strlen(cadena);
			
				/**PRACTICA Implementar aquí las acciones necesarias para crear un mensaje y un canal*/
				// Metemos la trama en el chat del canal
				
				//Guardamos el momento en el que se envio el mensaje
				sprintf(fecha, "%02d:%02d:%d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
				memcpy(trama_chat, fecha, 20);
				//Despues guardamos el canal*/
				memcpy(trama_chat + 20, canal, 20);
				//Despues escribimos el nombre del usuario
				memcpy(trama_chat + 2 * 20, usuario, 20);
				//Despues escribimos el entero que contiene la longitud del campo siguiente
				memcpy(trama_chat + 3 * 20, &longitud_camposiguiente, sizeof(uint16_t));
				//Por ultimo escribimos el mensaje
				memcpy(trama_chat + 3 * 20 + sizeof(uint16_t), cadena, longitud_camposiguiente);

				//Calculamos el tamanio total
				incremento = 3 * 20 + longitud_camposiguiente + sizeof(uint16_t);

				//Enviamos el mensaje		
		    	enviado = EnviarDatagramaEth(macdestino, trama_chat, incremento, TYPE2);
				
				//Si el valor obtenido es -1 se ha producido un error
				if (enviado==-1)
					printf("Error enviando trama\n");
		
				//Si hemos llegado aqui el mensaje se ha enviado correctamente
				printf("Mensaje enviado\n");
				
				//Ponemos el incremento a 0 para el envio del siguiente mensaje
				incremento=0;
			}
		}
		else if(strcmp(argv[1], "-a") == 0){
			//Envio aoutomatico de mensajes
			printf("Programa inciado para envio automatico de mensajes (se enviaran 200 mesnajes automaticamente)\n");
			//Generamos semilla para crear numeros aleatorios
			srand(time(NULL));
			//Bucle que envia mensajes automaticos para analizar la tasa de error*/
			i = 0;
			while(i < NUM_MENSAJES){
				//Utilizamos bzero para limpiar la caden
				bzero(cadena, 1456);
				//Generamos numero aleatorio para guardarlo en la cadena
				r = rand() % 255 + 0;
				//Escribimos el numero en la cadena del mensaje
				sprintf(cadena, "%d", r);
			
				//Especificamos que la longitud
				longitud_camposiguiente = LONGITUD;
			
				/**PRACTICA Implementar aquí las acciones necesarias para crear un mensaje y un canal*/
				//Metemos la trama en el canal
				
				//uardamos en la trama el momento en el que se envia el mensaje
				sprintf(fecha, "%02d:%02d:%d %02d:%02d:%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900, tm.tm_hour, tm.tm_min, tm.tm_sec);
				memcpy(trama_chat, fecha, 20);
				//Guardamos el canal para el que se transmite el mensaje
				memcpy(trama_chat + 20, canal, 20);
				//Escribimos el nombre del usuario que envia el mensaje
				memcpy(trama_chat + 2 * 20, usuario, 20);
				//Escribimos el entero que contiene la longitud del campo siguiente
				memcpy(trama_chat + 3 * 20, &longitud_camposiguiente, sizeof(uint16_t));
				//Escribimos el mensaje*/
				memcpy(trama_chat + 3 * 20 + sizeof(uint16_t), cadena, longitud_camposiguiente);

				//Calculamos el tamano total
				incremento = 3 * 20 + longitud_camposiguiente + sizeof(uint16_t);

				//Enviamos el mensaje*/			
		    	enviado = EnviarDatagramaEth(macdestino, trama_chat, incremento, TYPE2);
				
				//Si se produce un error la funcion devuelve -1 y se muestra por pantalla el error
				if (enviado==-1)
					printf("Error enviando trama\n");
				
				//Aumentamos en 1 el numero de mensajes y ponemos la variable incremento a 0 para generar correctamente el siguiente mensaje
				i++;
				incremento=0;	
			}

		}
		else{
			printf("Error en los argumentos del programa\n");
		}
    }

	finalizar=FinalizarEth();
	
	if (finalizar==-1){

		printf("Error finalizando\n");
		return(EXIT_FAILURE);
	}
	else{
		printf("Finalizacion correcta\n");
		return(EXIT_SUCCESS);
	}
}
