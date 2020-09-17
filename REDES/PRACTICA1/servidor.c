#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <signal.h>

#define MAX_CONNECTION 6
#define TAM 2048


int sockfd;
int newsockfd;
char directorio_recurso[500]={0}, recurso_predeterminado[500]={0};

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

//Devuelve informacion de un fichero, como el tamano en bytes
//Entrada:
//	char *ruta_fichero: Contiene la direccion en la que se encuentra el fichero
//	char *nombre_fichero: Contiene el nombre del fichero 
//	struct stat * info: Estructura en la que se guardara el tamano del fichero
//Salida:
//	int: Devuelve -1 si no encuentra el fichero o hay algun error
// 	     Devuelve 0 si no hay ningun error
//Comentarios
int fileInfo(char *ruta_fichero,char *nombre_fichero, struct stat * info) {
	char ruta_y_nombre_de_fichero[1024]={0};
	strcat(ruta_y_nombre_de_fichero,ruta_fichero);
	strcat(ruta_y_nombre_de_fichero,"/");
	strcat(ruta_y_nombre_de_fichero,nombre_fichero);

	printf("\nA buscar --%s--\n",ruta_y_nombre_de_fichero);

	if(stat(ruta_y_nombre_de_fichero,info)!=0)
		return -1;
	else
		return 0;
}

//Esta funcion devuelve informacion sobre el software que actua como servidor y los subproductos del mismo
//Entrada:
//	int *portno: Cadena de enteros que contiene el numero de puerto del servidor
//	char *recurso_defecto: El recurso por defecto al que se accede en caso de que el servidor no tenga respuesta 
//	char *directorio_de_recursos: La direccion en la que se encuentran los recursos a los que accede el servidor
//	char *nombre_fichero: El fichero que contiene la configuracion del servidor
//Salida:
//	int: Devuelve -1 si hay un error al abrir o al leer el fichero de configuracion del servidor
//	     Devuelve 0 si no hay ningun error
//Comentarios
int serverInfo(int *portno, char *recurso_defecto, char *directorio_de_recursos, char* nombre_fichero) {
	FILE *f;
	char linea[1000]={0};

	f=fopen (nombre_fichero,"r");
    if(f == NULL){
		printf("Error al abrir el fichero de configuración (%s).\n",nombre_fichero);
		return -1;
	}

    if (fgets(linea,1000,f) != NULL){
        printf ("--Leido %s--\n",linea);
        sscanf (linea, "%d %s %s", portno, recurso_defecto, directorio_de_recursos);
    }  
    else {
		printf("Error al leer el fichero de configuración.\n");
		return -1;
	}
    
    fclose(f);
	return 0; 
}

//Esta funcion indica el tipo MIME de los datos adjuntos tras la cabecera HTTP
//Entrada:
//	char *tipo: Cadena de caracteres que contiene el tipo MIME de los datos adjuntos
//	char *extension: Cadena de caracteres que contiene la extension de los datos adjuntos
//Salida:
//	int: Devuelve 0 si se encuentra el tipo MIME
//	     Devuelve 1 si la extension de los datos adjuntos esta en blanco o no se ha encontrado el tipo MIME
//	     Devuelve -1 si hay un error abriendo el fichero que contiene el tipo MIME
//Comentarios
int contentType(char *tipo, char* extension) {
  	FILE *faux;					
	tipo[0]=0;
	char comando[1000]={0};
	if(strlen(extension)==0)
		return 1;
	sprintf(comando,"awk '{for(i=2;i<=NR;i++){if($i==\"%s\")print $1}}' /etc/mime.types",extension);
    faux=popen(comando,"r");
    if(faux==NULL){
		printf("ERROR abriendo fichero auxilar popen\n");
		return -1; 
	}
    fscanf(faux,"%s",tipo);
	pclose(faux);
	if(strlen(tipo)==0)
		return 1;   //No encontrado!
	return 0;       //Encontrado!
}

void process_request(int newsockfd){
	char buffer[5000];
	int n,m;
	char metodo[50];
	char version[50];
	char recurso[500];
	char recurso_solicitado[1000];
	char* extension;
	char recurso_aux[500];
	char respuesta_buffer[1000];
	char tipo[500];
	char direccion_recurso[500];
	char *recurso_solicitado_aux;
	struct stat info;
	FILE *pf;
	bzero(buffer,5000);
	//leemos del socket hasta 5000 bytes
	n = read(newsockfd,buffer,5000);
	if (n < 0) 
		error("ERROR reading from socket");

	//Si no hay contenido que leer salimos
         if(strlen(buffer)==0)
         {
                 close(newsockfd);
                 return;
         }

/* Obtener método, recurso y versión de la petición HTTP almacenada en la variable buffer. Se recomienda el uso de la función sscanf.*/

	printf("La solicitud es %s\n",buffer);
	sscanf(buffer,"%s %s %s", metodo,recurso,version);
	printf("\nEl metodo es %s, el recurso es %s y la version %s\n", metodo, recurso, version);
	

/* Comprobar que el método de la petición sea GET y la versión HTTP/1.1 o HTTP/1.0*/

	if(strcmp("GET",metodo)!=0){
		printf("El metodo utilizado no es correcto\n");
		close(newsockfd);		
		return;
	}
	else if((strcmp("HTTP/1.1",version)!=0) && (strcmp("HTTP/1.0",version)!=0)){
		printf("La version utilizada no es HTTP/1.1 ni HTTP/1.0\n");	
		close(newsockfd);
		return;
	}
	
/* Comprobar si el recurso que se solicita es /.
        Si es /, simplemente el recurso solicitado es el recurso por defecto (tal como se leyó en el fichero de configuración).*/
	
	if(strcmp(recurso,"/")==0){
		strcpy(recurso_solicitado,recurso_predeterminado);
		printf("El recurso solicitado es del tipo /\n");
		strcpy(direccion_recurso,directorio_recurso);
		strcat(direccion_recurso,recurso);
		strcat(direccion_recurso,recurso_predeterminado);
	}
	else{	
		strcpy(direccion_recurso,directorio_recurso);
		strcat(direccion_recurso,recurso);
		printf("El recurso solicitado es del tipo /.\n");
		strcpy(recurso_aux,recurso);
		recurso_solicitado_aux=strtok(recurso_aux,"/");
		if(!recurso_solicitado_aux){
			//Si la solicitud no es del tipo /. ni / 
			sprintf(respuesta_buffer,"HTTP 404 Not Found\r\n\r\n");
			printf("Respuesta generada:%s\n",respuesta_buffer);
			n = write(newsockfd,respuesta_buffer,strlen(respuesta_buffer));
			if (n < 0) 
				error("ERROR writing to socket");

			//cerramos el socket nuevo que se ha creado en el otro sentido
			close(newsockfd);
			return;	
		}
		strcpy(recurso_solicitado,recurso_solicitado_aux);
	}
	
/* Se debe comprobar la existencia del recurso solicitado por el navegador. Para ello se recomienda el uso de la función stat.
    Si el recurso existe se debe devolver una cabecera HTTP 200 OK junto con el contenido del recurso (por ejemplo, web solicitada) solicitado.
        Para construir la cabecera de respuesta se recomienda el uso de la función sprintf. El contenido del campo   Content-Length se obtendrá de la función stat (ver código de ayuda) mientras que el contenido del campo Content-Type se obtendrá del fichero de mimes (ver código de ayuda).
        Para la lectura de los recursos (ficheros a enviar como respuesta) se debe hacer uso de la funcion fread y NO de la funcion fgets
    Si el recurso no existe se debe devolver una cabecera HTTP 404 Not Found que no contenga Content-Type ni Content-Length (mirar ejemplos enunciado, o Wireshark!).*/

	strcpy(recurso_aux,recurso_solicitado);
	if(fileInfo(directorio_recurso, recurso_solicitado, &info)==0){
		printf("Se ha encontrado el recurso solicitado\n");
		printf("El recurso solicitado es: %s\n",recurso_solicitado);
		strtok(recurso_aux,".");
	  	extension=strtok(NULL,"/");
		printf("La extension del recurso solicitado es: %s\n",extension);
		if(contentType(tipo,extension)==1){
			sprintf(respuesta_buffer,"%s 500 Internal Error\r\n\r\n",version);
			printf("Respuesta generada:%s\n",respuesta_buffer);
			n = write(newsockfd,respuesta_buffer,strlen(respuesta_buffer));
			if (n < 0) 
				error("ERROR writing to socket");
		}
		else{	
			sprintf(respuesta_buffer,"%s HTTP 200 OK %s solicitado\r\nContent-Type:%s\r\nContent-Length:%d\r\n\r\n",version,recurso_solicitado,tipo, (int)(info.st_size));
			printf("Respuesta generada:%s\n",respuesta_buffer);
			n = write(newsockfd,respuesta_buffer,strlen(respuesta_buffer));
			if (n < 0) 
				error("ERROR writing to socket");
			pf=fopen(direccion_recurso,"r");
			if(!pf){
				printf("Se ha producido un error al abrir el recurso\n");
				close(newsockfd);
				return;
			}
			printf("\nRECURSO ENCONTRADO Y ABIERTO CORRECTAMENTE\n\n");
			if((int)(info.st_size)<TAM){
				n=fread(respuesta_buffer, 1, TAM, pf);
			        write(newsockfd,respuesta_buffer, n);  
			}else{
				while(m<(int)(info.st_size)){
            				n=fread(respuesta_buffer, 1, TAM, pf);
					write(newsockfd,respuesta_buffer,n);  
					m=m+TAM;
         			}	
			}
			fclose(pf);	
		}
	}
	else{
		sprintf(respuesta_buffer,"HTTP 404 Not Found\r\n\r\n");
		printf("Respuesta generada:%s\n",respuesta_buffer);
		n = write(newsockfd,respuesta_buffer,strlen(respuesta_buffer));
		if (n < 0) 
			error("ERROR writing to socket");
	}

	//cerramos el socket nuevo que se ha creado en el otro sentido
	close(newsockfd);

}

void handle(int nsignal){
	printf("server is shutting down now\n");
	close(sockfd);
	close(newsockfd);
	exit(0);
}

int main(int argc, char *argv[])
{
	int portN;
	struct sockaddr_in serv_addr,cli_addr;
	int n, newsockfd;

	// Crear un socket para manejar conexiones TCP
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
		error("ERROR opening socket");

	/*Lectura de fichero de configuracion y asignacion de puerto a variable portN*/
	/**********************************/
	if(serverInfo(&portN,recurso_predeterminado,directorio_recurso,"fichero.config")==-1){
		printf("Se ha producido un error al leer el archivo de configuracion");
		close(sockfd);
		return -1;
	}
	printf("\nEl numero de puerto es %d, el directorio de recurso es %s y el recurso predeterminado es %s\n\n",portN,directorio_recurso,recurso_predeterminado);

	// Preparar una estructura con informacion sobre como vamos
	// a recibir las conexiones TCP
	// En este ejemplo, enlazaremos el socket a la IP local al puerto TCP PORT
	// Esto lo conseguiremos inicializando
	// la estructura a cero mediante, por ejemplo, 'bzero'.
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portN);
	

	// Activaremos una propiedad del socket que permitira que otros
	// sockets puedan reutilizar cualquier puerto al que nos enlacemos.
	// Esto permitira en protocolos como el TCP, poder ejecutar un
	// mismo programa varias veces seguidas y enlazarlo siempre al
	// mismo puerto. De lo contrario habria que esperar a que el puerto
	// quedase disponible (TIME_WAIT en el caso de TCP)
	if (setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&serv_addr,sizeof(struct sockaddr_in))==-1)
	{
 		error("ERROR: Fallo al reutilizar el puerto.\n");
	}

	if (bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
		error("ERROR on binding");

	/* Habilitar socket para recibir una conexion */
	if (listen(sockfd, MAX_CONNECTION) == -1){
		printf("Error en listen\n");
		close(sockfd);
		return -1;
	}

	/* Captura la senal SIGINT */
	if(signal(SIGINT,handle)==SIG_ERR)
	{
		error("ERROR: Fallo al capturar la senal SIGINT.\n");
	}

	/* While (true) */
	while (1){
		/* Espera de conexion */
		n = sizeof(struct sockaddr_in);
		if ((newsockfd=accept(sockfd,(struct sockaddr*)&cli_addr,(socklen_t *) &n)) == -1){
			printf("Error en accept\n");
			continue;
		}
		/* procesar peticion */
		process_request(newsockfd);
	}
	close(sockfd);
	return 0; 
}

