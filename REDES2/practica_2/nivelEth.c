#include <pthread.h>
#include <pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

#include "nivelEth.h"
#include "rc_funcs.h"



/******************************
*Arquitectura de Redes II     *
*Funciones de Nivel Ethernet  *
*Javier Ramos 2013-2014       *
* Manuel Ruiz 2017-2018       *
*******************************/

pthread_t t;
pcap_t  *p;

/*Variables globales*/
tpfNotificacionRecepcionEth funcion_notificacion;
uint16_t tipos[2];
int n_tipos;
int NivelEthIniciado;
uint64_t preambulo = 0xAAAAAAAAAAAAAAAB;



/************************************************************************************************
*Funcion:getMACAddr 									                                     	*
*Descripcion: Obtiene la direccion MAC de una interfaz						                    *
*Entrada:											                                            * 
*	mac:vector de 6 bytes a rellenar con la MAC de la interfaz				                    *
*	interface: nombre la de interfaz de la cual se obtendra la MAC. Por ejemplo "eth0"	        *
*Retorno: Ninguno										                                        *
*************************************************************************************************/

void getMACAddr(uint8_t *mac,char *interface)
{
    
    int s;
    struct ifreq ifr;
    s = socket(AF_INET, SOCK_DGRAM, 0);
    strcpy(ifr.ifr_name, interface);
    ioctl(s, SIOCGIFHWADDR, &ifr);
    memcpy(mac,ifr.ifr_hwaddr.sa_data,HWADDR_len);
  
}
/************************************************************************************************
*Funcion:attendPacket																			*
*Descripcion: Esta funcion se ejecuta cada vez que se recibe un paquete. Aqui dentro debe		*
*	      ejecutarse cualquier operación sobre el paquete recibido								*
*Entrada:																						* 
*	user:informacion pasada a nivel de usuario por la libreria pcap (desde pcap_loop)			*
*	h: esructura de cabecera pcap del paquete recibido (tiempo y tamanyo)						*
*	packet: buffer con el contenido binario del paquete											*
*Retorno: Ninguno																				*
*************************************************************************************************/
void attendPacket(u_char *user,const struct pcap_pkthdr *h,const u_char *packet)
{
	uint8_t mac_destino[ETH_ALEN];
	uint8_t mac_origen[ETH_ALEN];
	uint16_t aux16;
	uint8_t mensaje[ETH_MAX_LEN];
	uint32_t crc;
	uint32_t auxcrc;
	uint64_t aux64;
	uint8_t macdestino[6] = {0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};
	uint32_t size=0;

	int i, flag = 0;


	/**PRACTICA Implementar aquí las acciones necesarias al recibir un paquete*/
	if(!h || !packet){
		printf("Error en los parametros\n");
		return;
	}

	if(NivelEthIniciado == 1){
		memcpy(&aux64, packet + size, sizeof(uint64_t));

		if(aux64 != preambulo){
			return;
		}
		size += sizeof(uint64_t);
		memcpy(mac_destino, packet + size, ETH_ALEN);
		size += ETH_ALEN;

		if(strncmp((const char *)macdestino, (const char *)mac_destino, ETH_ALEN) != 0){
			return;
		}
		memcpy(mac_origen, packet + size, ETH_ALEN);
		size += ETH_ALEN;
		memcpy(&aux16, packet + size, ETH_TLEN);
		size += ETH_TLEN;

		for(i = 0; i < n_tipos; i++){
			if(strncmp((const char *)&aux16, (const char *)&tipos[i], ETH_TLEN) == 0)
				flag = 1;
		}

		if(flag == 0){
			return;
		}

		memcpy(mensaje, packet + size, (h->len - (size + CRC_LEN)));
		size += (h->len - (size + CRC_LEN));

		memcpy(&auxcrc, packet + size, CRC_LEN);

		crc = crc32((h->len-CRC_LEN), (uint8_t*)packet);
		if(crc != auxcrc){
			return;
		}

		funcion_notificacion(mac_origen, ((h->len) - (ETH_HLEN + CRC_LEN)), mensaje, aux16, &h->ts);
	}
}


/************************************************************************************************
*Funcion:startCapture																			*
*Descripcion: Esta funcion se ejecuta en un hilo nuevo e inicia la captura de paquetes a		*
*	      través de la función pcap_loop. Se ejecuta en un nuevo hilo parta evitar que el 		*
*	      programa principal quede bloqueado al llamar a la función InicializarNivel1a			*
*Entrada:																						*	
*	arg: argumentos del hilo. En nuestro caso ninguno											*
*Retorno: Ninguno																				*
*************************************************************************************************/
void * startCapture(void *arg)
{
	pcap_loop(p,-1,attendPacket,NULL);
	return NULL;
}

/************************************************************************************************
*Funcion:InicializarStackRed																	*
*Descripcion: Esta funcion inicia el nivel1a registrando la función de notificación, abriendo 	*
*	      una captura live pcap y lanzando un hilo de proceso de paquetes						*
*																								*
*************************************************************************************************/
int InicializarEth(uint16_t *Tipos, uint8_t nType, tpfNotificacionRecepcionEth funcion, int timeout)
{
	char errbuff[1000];
	int i, iret;

	/**PRACTICA Implementar aquí las acciones necesarias para inciar el nivel Ethernet*/
	n_tipos = nType;

	for(i = 0; i < n_tipos; i++){
		tipos[i] = Tipos[i];
	}
	// Para abrir la interfaz hemos usado una macro en la que definimos la interfaz, en los laboratorios siempre eth0
	p = pcap_open_live(INTERFACE,ETH_MAX_LEN,1,timeout,errbuff); //abre la interfaz eth0 en modo promiscuo, es decir, analiza todas las tramas que le llegan, tenemos que ver si son para nosotros o no (ver la direccion de destino) 
	if (p == NULL){
		printf ("Error: %s\n", errbuff);//el error se guarda en errbuff
		return ETH_ERROR;
	}

	iret = pthread_create(&t,NULL,startCapture,NULL);
	// Si devuelve 0 significa que se ha producido un error
	if(iret != 0){
		printf("Se ha producido un error en la creacion del hilo\n");
		return ETH_ERROR;
	}

	NivelEthIniciado = 1;
	funcion_notificacion = funcion;
	
	return 0;
	
}

/************************************************************************************************
*Funcion:FinalizarEth																			*
*Descripcion: Esta funcion finaliza el nivel1a liberando los recursos que se hayan reservado y 	*
*	      cerrando la captura live pcap															*
*																								*
*************************************************************************************************/
int FinalizarEth(void)
{
	/**PRACTICA Implementar aquí las acciones necesarias para finalizar el nivel Ethernet*/
	if(NivelEthIniciado == 1){
		pcap_breakloop(p);
		pthread_join(t, NULL);
		pcap_close(p);
		return 1;
	}

	printf("La captura ya se encontraba cerrada\n");
	return ETH_ERROR;
}

/************************************************************************************************
*Funcion:EnviarDatagramaEth																		*
*Descripcion: Esta funcion anyade una cabecera Ethernet y el CRC al mensaje pasado 				*
*             como argumento y lo envía utilizando la funcion pcap_inject						*
*																								*
*************************************************************************************************/

int EnviarDatagramaEth(const uint8_t *direccion_destino, const  uint8_t *mensaje, uint16_t tamano, uint16_t tipo)
{
	u_char buffer[ETH_MAX_LEN]={0};
	uint32_t size = 0;
	uint8_t mac_origen[6];
	uint32_t crc;

	/**PRACTICA Implementar aquí las acciones necesarias para enviar un paquete*/
	if(NivelEthIniciado == 1){
		memcpy(buffer, &preambulo, sizeof(uint64_t));
		size += sizeof(uint64_t);

		getMACAddr(mac_origen, INTERFACE);
		memcpy(buffer + size, direccion_destino, ETH_ALEN);
		size+=ETH_ALEN;
		memcpy(buffer+size, mac_origen, ETH_ALEN);
		size+=ETH_ALEN;
		memcpy(buffer+size, &tipo, ETH_TLEN);
		size+=ETH_TLEN;
		memcpy(buffer+size, mensaje, tamano);
		size+=tamano;
		crc=crc32(size, buffer);
		memcpy(buffer+size, &crc, CRC_LEN);
		size+=CRC_LEN;
		pcap_inject(p, buffer, size);

		return 0;
	}
	return 	ETH_ERROR;
}
