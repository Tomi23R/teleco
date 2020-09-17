#include <stdio.h>
#include <string.h>
#define MAX_NOMBRE 128
int main(int argc, char *argv[])
{
    char nombre[MAX_NOMBRE];
    int tam;
    int num_libros;
    int i;
    char * libros[] = {
        "1984",
        "Yo, robot",
        "20000 leguas de viaje submarino",
        "Un mundo feliz"
    };
    
    /* Calculo del tamaño del array de libros. */
    num_libros = sizeof(libros) / sizeof(char *);

    /* Pedir por pantalla el nombre del libro */
    printf("Introduce el nombre del libro: ");
    fgets(nombre, MAX_NOMBRE, stdin);

    /* Eliminar el posible retorno de carro leído por fgets*/
    tam = strlen(nombre);
    if ( nombre[tam - 1] == '\n' ) {
        nombre[tam - 1] = '\0';
    }
    
    /* Tu código */
    for(i = 0; i < num_libros; i++){
        if(strcmp(libros[i],nombre) == 0){
            printf("El índice es %d\n",i);
            return 0;
        }
    }
    
    printf("No se ha encontrado el libro \"%s\"\n",nombre);
    
    return 0;
}