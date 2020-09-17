// Ejemplo de sockets en Linux que mandan y reciben datagramas UDP
#include <stdio.h>
#include <stdlib.h>

// Estas cabeceras son necesarias para los 'sockets'
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>  // Usado por 'timeval'
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>  // Usado por 'close'
#include <stdint.h>
#include <string.h>  // Usado por 'strlen'

#define DNS_SERVER "64.6.64.6"
#define DNS_PORT 53
#define MAX_DATAGRAM_SIZE 4196


uint16_t id=0;

/****************************************************************************************
*Nombre: getNameDNS									*
*Descripcion: Esta funcion devuelve el nombre en formato DNS realizando			*
*	      reconstrucciones siguiendo los punteros DNS				*	
*Argumentos:										*
*	-data: puntero al lugar de la trama donde comienza el nombre que se desea 	*
*	      reconstruir								*
*	-datagramStart: puntero al comienzo del mensaje DNS				*
*	-reconstructedName: cadena de caracteres donde se guardara el nombre 		*
*	    reconstruido. Debe ser una cadena con tamaño reservado			*
*Retorno: - La funcion devuelve el numero de caracteres que se han leido hasta encontrar*
*	  el primer puntero DNS en caso de que los haya o hasta encontrar el final de 	*
*	  la cadena DNS									* 
	-reconstructedName (como argumento)						*
*											*
****************************************************************************************/
int getNameDNS(uint8_t *data,uint8_t *datagramStart,char *reconstructedName)
{

	uint8_t *aux=data;
	int j=0,k=0,flag=0;

	while(aux[0]!=0)
	{

		if(aux[0]==0xC0)
		{
			aux=datagramStart+aux[1];
			if(flag==0)
			{
				flag=1;
				k++;
			}

		}
		else
		{
			reconstructedName[j]=((char)aux[0]);
			j++;
			aux++;
			if(flag==0)
			k++;
		}
	}

	return k+1;
}


/****************************************************************************************
*Nombre: domain2DNS									*
*Descripcion: Esta funcion convierte un nombre de dominio de la forma www.google.es	*
*	      al formato de cadena de DNS (3www6google2es0) OJO los numeros de la 	*
*	      cadena estan en valor decimal y no en ASCII				*
*Funcionamiento: A RELLENAR								*
*Argumentos:										*
*	-domain: nombre de dominio en formato estandar					*
*	-DNSname: nombre de dominio en formato DNS					*
*Retorno: la funcion devuelve la longitud de la cadena DNSname o -1 en caso de error	*
*											*
****************************************************************************************/
int domain2DNS(char *domain,char *DNSname)
{
	char *token;
	int i, j = 0;
	
	if(!domain || !DNSname)
		return -1;

	token = strtok(domain, ".");
	while(token != NULL){
		i = strlen(token);
		DNSname[j]=i;
		j = j+1;
		strcpy(DNSname+j, token);
		j = j+i;
		token = strtok(NULL, ".");
	}
	DNSname[j]=0;
	return j+1;
}


/****************************************************************************************
*Nombre: DNS2domain									*
*Descripcion: Esta funcion convierte un nombre en formato DNS(3www6google2es0) a un 	*
*	      nombre de dominio estandar (www.google.es). OJO los numeros de la cadena	*
*	      estan en valor decimal y no en ASCII	 
*Funcionamiento: A RELLENAR				*
*Argumentos:										*
*	-DNSname: nombre de dominio en formato DNS					*										
*	-domain: nombre de dominio en formato estandar					*
*Retorno: la funcion devuelve la longitud de name o -1 en caso de error			*
*											*
****************************************************************************************/
int DNS2domain(char *DNSname,char *domain)
{
	int i=0, j=0, n=0;

	if(!domain || !DNSname)
		return -1;

	while (DNSname[j] != 0){
		n = DNSname[j];
		j++;
		strncpy(domain+i,DNSname+j,n);
		j+=n;
		i+=n;
		strncpy(domain+i,".",1);
		i++;
	}
	domain[i-1]=0;
	return i;
}


/****************************************************************************************
*Nombre: buildQuery									*
*Descripcion: Esta funcion construye una peticion DNS rellenando la variable datagram	*
*Argumentos:										*
*	-datagram: array de bytes donde se construira la peticion DNS			*
*	-namee: nombre de dominio a resolver (ej. www.uam.es)				*
*Retorno: la funcion devuelve un entero indicando la longitud de datos utiles contenidos*
*	 en la variable datagram. En caso de error devuelve -1.				*
*											*
****************************************************************************************/

int buildQuery(uint8_t * datagram, char *namee)
{
	uint16_t aux16=0;
	uint32_t size=0;
	uint16_t flags=0x0100; //banderas todos los campos a 0 para peticion menos bit RD a 1	
	uint16_t number_questions=1,number_answers=0,number_auth=0,number_additional=0, tipo=1, clase=1;
	char DNSname[500];
	int n;

	//Se copia el ID de peticion DNS. EL identificador se incrementa para cada peticion
	aux16=htons(id);
	id++;
	memcpy(datagram+size,&aux16,sizeof(uint16_t));
	size+=sizeof(uint16_t);

	//se copian los flags
	aux16=htons(flags);
	memcpy(datagram+size,&aux16,sizeof(uint16_t));
	size+=sizeof(uint16_t);

	//se copian el numero de preguntas a realizar (en nuestro caso 1)
	aux16=htons(number_questions);
	memcpy(datagram+size,&aux16,sizeof(uint16_t));
	size+=sizeof(uint16_t);


	//se copian el numero de respuestas que se envian (en nuestro caso 0)
	aux16=htons(number_answers);
	memcpy(datagram+size,&aux16,sizeof(uint16_t));
	size+=sizeof(uint16_t);


	//se copian el numero de respuestas de autoridades que se envian (en nuestro caso 0)
	aux16=htons(number_auth);
	memcpy(datagram+size,&aux16,sizeof(uint16_t));
	size+=sizeof(uint16_t);


	//se copian el numero de respuestas de adicionales que se envian (en nuestro caso 0)
	aux16=htons(number_additional);
	memcpy(datagram+size,&aux16,sizeof(uint16_t));
	size+=(1 * sizeof(uint16_t));
	
	/*PRACTICA IMPLEMENTAR AQUI*/
	/*Construir resto de la cabecera. Para ello:
		-Convertir la variable namee a formato DNS y copiarla con memcpy
		-Copiar con memcpy el campo tipo rellenando con valor A (1)
		-Copiar con memcpy el campo clase rellenando con valor IN (1)
	*/

	/*-Convertir la variable namee a formato DNS y copiarla con memcpy*/
	n=domain2DNS(namee, DNSname);
	memcpy(datagram+size,DNSname,n);
	size+=n;

	/*-Copiar con memcpy el campo tipo rellenando con valor A (1)*/
	aux16=htons(tipo);
	memcpy(datagram+size,&aux16,sizeof(uint16_t));
	size+=(1 * sizeof(uint16_t));
	
	/*-Copiar con memcpy el campo clase rellenando con valor IN (1)*/
	aux16=htons(clase);
	memcpy(datagram+size,&aux16,sizeof(uint16_t));
	size+=(1 * sizeof(uint16_t));
	
	return size;	
}



/****************************************************************************************
*Nombre: parseDNSResponse								*
*Descripcion: Esta funcion analiza una respuesta DNS almacenada en la variable datagram	*
*	      La respuesta tendra la longitud indicada en la variable size		*
*Argumentos:										*
*	-datagram: array de bytes donde se encuentra la respuesta DNS			*
*	-size: tamano en bytes de la respuesta DNS					*
*Retorno: La funcion devuelve 0 si todo es correcto y -1 en caso contrario		*
*											*
****************************************************************************************/

int parseResponse(uint8_t * datagram, int size)
{
	uint16_t aux16=0;
	uint16_t flags=0;	
	uint16_t auxId=0;
	uint32_t sizeRead=0,TTL=0,aux32;
	uint16_t number_questions=0,number_answers=0,number_auth=0,number_additional=0,tipo=0,clase=0,RdataLen=0;
	int n,i=0;
	char domain[1000]={0},DNSname[1000]={0};

	//Se extrae el identificador de la peticion DNS
	memcpy(&aux16,datagram+sizeRead,sizeof(uint16_t));
	auxId=ntohs(aux16);
	sizeRead+=sizeof(uint16_t);
	
	//Se debe comprobar que el identificador de la respuesta coincide con el de la pregunta (id-1)
	if(auxId != (id-1))
		return -1;

	//Se extraen las flags
	memcpy(&aux16,datagram+sizeRead,sizeof(uint16_t));
	flags=ntohs(aux16);
	sizeRead+=sizeof(uint16_t);
	
	//Se debe comprobar que el bit QR de las banderas esta a 1 y los bits Rcode a 0 (No error)
	if( ((flags>>15)&0x0001)!=1)
		return -1;

	if(((flags)&0x000F)!=0)
		return -1;

	//Se extrae el numero de preguntas que vienen incluidas en la respuesta DNS
	memcpy(&aux16,datagram+sizeRead,sizeof(uint16_t));
	number_questions=ntohs(aux16);
	sizeRead+=sizeof(uint16_t);

	//Se extrae el numero de respuestas que vienen incluidas en la respuesta DNS
	memcpy(&aux16,datagram+sizeRead,sizeof(uint16_t));
	number_answers=ntohs(aux16);
	sizeRead+=sizeof(uint16_t);

	//Se extrae el numero de respuestas autoritativas que vienen incluidas en la respuesta DNS
	memcpy(&aux16,datagram+sizeRead,sizeof(uint16_t));
	number_auth=ntohs(aux16);
	sizeRead+=sizeof(uint16_t);

	//Se extrae el numero de respuestas adicionales que vienen incluidas en la respuesta DNS
	memcpy(&aux16,datagram+sizeRead,1 * sizeof(uint16_t));
	number_additional=ntohs(aux16);
	sizeRead+=sizeof(uint16_t);

	for(i=0;i<number_questions;i++)
	{
		printf("Pregunta %d\n",i);
	/*PRACTICA IMPLEMENTAR AQUI*/
	/*Leer preguntas incluidas en la respuesta DNS. Para ello:
		-Leer y convertir a formato estandar el campo query name 
		-Leer el campo tipo
		-Leer el campo clase 
		-Comprobar que tipo y clase estan a 1
	*/
	
		/*-Leer y convertir a formato estandar el campo query name*/
		n=getNameDNS(datagram+sizeRead,datagram,DNSname);
		DNS2domain(DNSname,domain);
		sizeRead+=n;

		/*-Leer el campo tipo*/
		memcpy(&aux16,datagram+sizeRead,1 * sizeof(uint16_t));
		tipo=ntohs(aux16);	
		sizeRead+=sizeof(uint16_t);

		/*-Leer el campo clase*/
		memcpy(&aux16,datagram+sizeRead,1 * sizeof(uint16_t));
		clase=ntohs(aux16);
		sizeRead+=sizeof(uint16_t);

		/*-Comprobar que tipo y clase estan a 1*/
		if(clase!=1 || tipo!=1){
			printf("ERROR AL GENERAR LA PREGUNTA\n");
			return -1;
		}
	}

	for(i=0;i<number_answers;i++)
	{
		printf("Respuesta %d\n",i);
	/*PRACTICA IMPLEMENTAR AQUI*/
	/*Leer respuestas incluidas en la respuesta DNS. Para ello:
		-Leer y convertir a formato estandar el campo name (ojo el campo name puede contener punteros DNS)
		-Leer el campo tipo para obtener si la repsuesta es una IP A(valor 1) o un nombre canonico CNAME(valor 5)
		-Leer el campo clase y comprobar que es IN(valor 1)
		-Leer el campo TTL (no sera usado en esta practica)
		-Leer el campo RdataLen. Este campo valdra 4 en caso de que la respuesta sea de tipo 1 o un numero
		variable en caso de que el tipo sea 5.
		-Leer e imprimir RDATA. En caso de respuestas de tipo 1, imprimir por pantalla la IP. En caso de peticiones de tipo 5
		imprimir por pantalla el nombre canonico. En caso de respuestas de tipo 5 el campo RDATA puede contener punteros DNS.
	*/
		
		/*-Leer y convertir a formato estandar el campo name (ojo el campo name puede contener punteros DNS)*/
		bzero(DNSname,1000);
		n=getNameDNS(datagram+sizeRead,datagram,DNSname);
		DNS2domain(DNSname,domain);
		printf("Name: %s\n",domain);
		sizeRead+=n;

		/*-Leer el campo tipo para obtener si la repsuesta es una IP A(valor 1) o un nombre canonico CNAME(valor 5)*/
		memcpy(&aux16,datagram+sizeRead,1 * sizeof(uint16_t));
		tipo=ntohs(aux16);
		sizeRead+=sizeof(uint16_t);
		if((tipo!=1) && (tipo!=5)){
			printf("TIPO INCORRECTO\n");
			return -1;
		}	

		
		/*-Leer el campo clase y comprobar que es IN(valor 1)*/	
		memcpy(&aux16,datagram+sizeRead,1 * sizeof(uint16_t));
		clase=ntohs(aux16);
		sizeRead+=sizeof(uint16_t);
		if(clase!=1){
			printf("CLASE INCORRECTA\n");
			return -1;
		}
		
		/*-Leer el campo TTL (no sera usado en esta practica)*/	
		memcpy(&aux32,datagram+sizeRead,1 * sizeof(uint32_t));
		TTL=ntohs(aux32);
		sizeRead+=sizeof(uint32_t);
		
		/*-Leer el campo RdataLen. Este campo valdra 4 en caso de que la respuesta sea de tipo 1 o un numero
		variable en caso de que el tipo sea 5.*/
		memcpy(&aux16,datagram+sizeRead,1 * sizeof(uint16_t));
		RdataLen=ntohs(aux16);
		sizeRead+=sizeof(uint16_t);
		if(tipo==1){
			if(RdataLen!=4){
				printf("ERROR EN RdataLen\n");
				return -1;
			}
		}
		else{
			if(RdataLen==4){
				printf("ERROR EN RdataLen\n");
				return-1;
			}
		}
		
		/*-Leer e imprimir RDATA. En caso de respuestas de tipo 1, imprimir por pantalla la IP. En caso de peticiones de tipo 5
		imprimir por pantalla el nombre canonico. En caso de respuestas de tipo 5 el campo RDATA puede contener punteros DNS.*/		
		if(tipo==1){
			printf("IP: %u.%u.%u.%u\n",datagram[sizeRead],datagram[sizeRead+1],datagram[sizeRead+2],datagram[sizeRead+3]);
			sizeRead+=4;
		}
		else{
			bzero(DNSname,1000);
			n=getNameDNS(datagram+sizeRead,datagram,DNSname);
			DNS2domain(DNSname,domain);
			printf("Nombre canonico:%s\n",domain);
			sizeRead+=n;
		}
			
	}

	return 0;	
}

int main(int argc, char *argv[])
{
   struct sockaddr_in  sock_addr, to_addr;
   socklen_t           sockaddrlen = sizeof(struct sockaddr);
   int                 sock, c;
   struct timeval      tv;     // Usado para el 'timeout'
   fd_set              rfds;   // Usado por el 'select'
   uint8_t        datagram[MAX_DATAGRAM_SIZE]={0};
	
   int n=0;
   fprintf( stdout, "Programa de ejemplo cliente DNS...\n");
  

	if(argc > 2 && argc <= 1)
	{
		printf("Numero de argumentos incorrectos\n");
		printf("Uso: ./nslookup direccion\n");
		exit(-1);
	}
	// Crear un socket para manejar datagramas UDP
	sock = socket( AF_INET, SOCK_DGRAM, 0 );
	if(sock == -1)
	{
		perror("El socket no pudo ser creado!\n");
		exit(-1);
	} //endif

	// Activaremos una propiedad del socket que permitira que otros
	// sockets puedan reutilizar cualquier puerto al que nos enlacemos.
	// Esto permitira en protocolos como el TCP, poder ejecutar un
	// mismo programa varias veces seguidas y enlazarlo siempre al
	// mismo puerto. De lo contrario habria que esperar a que el puerto
	// quedase disponible (TIME_WAIT en el caso de TCP)
	c = 1;  // Opción requerida por 'setsockopt'
	setsockopt( sock, SOL_SOCKET, SO_REUSEADDR, (char *)&c, sizeof(c) );

	// Otro problema que hay que resolver es el bloqueo que se produce
	// en las funciones de envio y recepcion de informacion.
	// Si no se le indica nada al socket, todas las operaciones son 
	// bloqueantes. Esto afecta especialmente a la recepcion de datos,
	// puesto que hasta que no lleguen, la funcion no devolvera el
	// control. Para evitar bloqueos se puede usar la funcion 'select'
	// antes de recibir datos. Aqui solamente se van a preparar las
	// estructuras y el timeout que usara el 'select'.
	FD_ZERO( &rfds );
	// Activar el 'indicador de lectura' asociado al socket creado.
	// Cuando se reciban datos, se activara el 'indicador de lectura'.
	FD_SET( sock, &rfds);
	tv.tv_sec  = 2;  // Segundos del 'timeout'.
	tv.tv_usec = 0;  // Microsegundos del 'timeout'.

	// Preparar una estructura con informacion sobre como vamos
	// a recibir los datagramas UDP
	// En este ejemplo, enlazaremos el socket a la IP local a cualquier 
	// puerto UDP que esta libre. Esto lo conseguiremos inicializando
	// la estructura a cero mediante, por ejemplo, 'bzero'.
	// Si especificasemos un puerto mediante el comando:
	//    sock_addr.sin_port = htons(port);
	// entonces forzariamos el enlace del socket al puerto numero 'port'
	bzero( (char *)&sock_addr, sizeof(sock_addr) );
	sock_addr.sin_family = AF_INET;

	// Enlazar el socket creado al puerto que hemos descrito usando
	// la estructura anterior. Este paso es obligatorio si se desea
	// recibir cualquier datagrama.
	if( bind(sock, (struct sockaddr *)&sock_addr, sizeof(sock_addr) ) == -1 )
	{
		perror("El socket no pudo ser enlazado a un puerto libre !\n");
		exit(-1);  // No se pudo enlazar el socket. Habria que reintentarlo...
	} //endif

	// Preparar una estructura donde indicaremos la direccion IP a donde
	// vamos a enviar los datagramas y el puerto al que queremos que vayan
	// dirigidos.
	to_addr.sin_addr.s_addr = inet_addr(DNS_SERVER);// IP del DNS de Google
	to_addr.sin_port = htons(DNS_PORT);			// Puerto del DNS
	to_addr.sin_family = AF_INET;

	// Enviaremos un datagrama a dicha direccion IP y puerto, con unos
	// datos de ejemplo.
	// En el caso de la practica de DNS, estos datos corresponderan
	// con una trama DNS que se explica en el guion de la practica.

   
	if((n=buildQuery(datagram,argv[1]))<0)
	{
		 perror("Error construyendo peticion DNS\n");
		exit(-1);
	}
   	
	c = sendto( sock,datagram,n, 0, (struct sockaddr *)&to_addr, sockaddrlen );
	if(c == -1)
	{
		perror("No se pudo enviar el datagrama por el socket !\n");
		close( sock );
		exit(-1);
	} //endif

	// NOTA IMPORTANTE 1:
	// Cuando se envia un datagrama UDP a traves de un socket enlazado,
	// el puerto UDP de destino es el indicado por la estructura usada en
	// funcion 'sendto'. Pero el puerto UDP de origen es el que se uso
	// en la funcion 'bind' (que en este ejemplo es el primero libre que haya)
	// Cuando un servidor UDP recibe un 'request' en un puerto dedicado y
	// bien conocido (como es el 53 para el DNS), la respuesta la envia
	// al puerto de origen que le viene en el datagrama recibido.

	// NOTA IMPORTANTE 2:
	// Como ya se ha indicado arriba, la recepcion de datos no es bloqueante.
	// Tras un determinado 'timeout' la funcion 'select' devolvera un error 
	// si no se han recibido datos por el socket. En caso contrario, la 
	// funcion 'select' indicara que ya hay datos disponibles y entonces
	// podremos llamar a 'recvfrom' sin que se produzca un bloqueo.

	// Por lo tanto, esperaremos la respuesta del servidor por nuestro 
	// puerto de origen (fuere cual fuere) que hemos enlazado al principio.

	c = select( FD_SETSIZE, &rfds, (fd_set *)NULL, (fd_set *)NULL, &tv );
	if(c == -1)
	{
		perror("El 'select' tuvo un error !\n");
		close(sock);
		exit(1);
	} //endif

	if(c == 0)
	{
		// El 'select' ha indicado que el tiempo indicado en 'tv' ha acabado
		fprintf( stdout, "Timeout expirado... Respuesta no recibida !\n");
	}
	else
	{
		// El 'select' ha indicado que hay datos pendientes de ser recibidos
		c = recv( sock, datagram, MAX_DATAGRAM_SIZE, 0 );

		// Nota: La funcion 'recvfrom' hace lo mismo, solo que ademas tambien
		//       rellena una estructura indicando desde que direccion IP nos
		//       han enviado el datagrama, y cual es el puerto de origen.

		if(c == -1)
		{
			perror("Error al tratar de recibir un datagrama UDP !\n");
			close( sock );
			exit(-1);
		} //endif

		// Mostrar los datos recibidos. Si hemos mandado basura al DNS
		// nos contestara con una trama indicando que hay un error en la
		// estructura del 'query' que le enviamos.
		fprintf(stdout, "Datos obtenidos:");
		if(parseResponse(datagram,c)<0)
		{
			 perror("Error al procesar un datagrama UDP !\n");
			 if (sock) close( sock );
			 exit(-1);
		}
	} //endif
	fprintf(stdout, "\n");
   
   // Cerrar el socket y volver
	close( sock );
   
   return 0;
}
