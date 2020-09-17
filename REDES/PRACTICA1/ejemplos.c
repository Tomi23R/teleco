/*
8800 index.html /home/jlgd/ 
Ejemplos de uso de funciones necesarias para el desarrollo de la practica 1
Al incluirlas de cualquier forma en la entrega deben ser completadas sus cabeceras,
y los convenientes controles de error anadidos
 
 Compila: gcc -Wall -o ejemplos ejemplos.c
 Autor: Jose Luis Garcia Dorado
 2017 EPS-UAM 
**/


#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//AÑADIR CABECERA! (obligatorio para usar esta funcion), al menos:
//contentType, 21-10-17
//Esta funcion indica el tipo MIME de los datos adjuntos tras la cabecera HTTP
//Entrada:
//	char *tipo: Cadena de caracteres que contiene el tipo MIME de los datos adjuntos
//	char *extension: Cadena de caracteres que contiene la extension de los datos adjuntos
//Salida:
//	int: Devuelve 0 si se encuentra el tipo MIME
//	     Devuelve 1 si la extension de los datos adjuntos esta en blanco o no se ha encontrado el tipo MIME
//	     Devuelve -1 si hay un error abriendo el fichero que contiene el tipo MIME
//Comentarios
int funcion1(char *tipo, char* extension) {
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


//AÑADIR CABECERA! (obligatorio para usar esta funcion)
//OJO a los retornos
//serverInfo, 21-10-17
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
int funcion2(int *portno, char *recurso_defecto, char *directorio_de_recursos, char* nombre_fichero) {
	FILE *f;
	char linea[1000]={0};

	f=fopen (nombre_fichero,"r");
    if(f == NULL){
		printf("Error al abrir el fichero de configuración (%s).\n",nombre_fichero);
		return -1;
	}

	if (fgets(linea,1000,f) == NULL){
		printf("Error a leer el fichero de configuración.\n");
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



//AÑADIR CABECERA! (obligatorio para usar esta funcion)
//fileInfo, 21-10-17	
//Devuelve informacion de un fichero, como el tamano en bytes
//Entrada:
//	char *ruta_fichero: Contiene la direccion en la que se encuentra el fichero
//	char *nombre_fichero: Contiene el nombre del fichero 
//	struct stat * info: Estructura en la que se guardara informacion del fichero si ha sido encontrado
//Salida:
//	int: Devuelve -1 si no encuentra el fichero o hay algun error
// 	     Devuelve 0 si no hay ningun error
//Comentarios
int funcion3(char *ruta_fichero,char *nombre_fichero, struct stat * info) {
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


//Ejemplos de uso de las funciones dadas

int main(int argc, char *argv[])
{
	char tipo[256]={0};
	int ret, portno=0;
	char extension[64]={0};
	char recurso_defecto[1000]={0}, directorio_de_recursos[1000]={0};
	struct stat info;

		//f1
	sprintf(extension,"%s","movie");
	ret=funcion1(tipo,extension);
	printf("El mime type de %s es %s (retorno=%d)\n",extension,tipo,ret);

	sprintf(extension,"%s","sdfsdgfdg");
	ret=funcion1(tipo,extension);
	printf("El mime type de %s es %s (retorno=%d)\n",extension,tipo,ret);

	sprintf(extension,"%s","html");
	ret=funcion1(tipo,extension);
	printf("El mime type de %s es %s (retorno=%d)\n",extension,tipo,ret);

	sprintf(extension,"%s","pdf");
	ret=funcion1(tipo,extension);
	printf("El mime type de %s es %s (retorno=%d)\n",extension,tipo,ret);

	sprintf(extension,"%s","");
	ret=funcion1(tipo,extension);
	printf("El mime type de %s es %s (retorno=%d)\n",extension,tipo,ret);



		//f2
	sprintf(extension,"%s","");
	ret=funcion2(&portno, recurso_defecto, directorio_de_recursos,"ejemplos.c");
	printf("Se ha leido un puerto=%d_, un recurso por defecto=%s_, y un directorio de recursos=%s_\n",portno,recurso_defecto,directorio_de_recursos);



		//f3
	ret=funcion3("/etc/","mime.types", &info);
	printf("El fichero mime.types tiene un tamano de %ld bytes.\n\n",info.st_size);



	return 0;
}

