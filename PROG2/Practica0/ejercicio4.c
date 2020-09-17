#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TAM 500

int main(int argc, char** argv){
    FILE* pf;
    int anio, max, min;
    char nombre[TAM], mayor[TAM], menor[TAM], cadena[TAM];
    char* aux;
    
    if(argc < 2){
        printf("Error, debes introducir el nombre del fichero como argumento del programa\n");
        return -1;
    }
    
    pf=fopen(argv[1], "r");
    
    if(!pf){
        printf("Nombre del fichero incorrecto\n");
        return -1;
    }
    
    fgets(cadena, TAM, pf);
    
    aux = strtok(cadena, "|");
    aux = strtok(NULL, "|");
    strcpy(nombre, aux);
    aux = strtok(NULL, "|");
    anio = atoi(aux);
    max = anio;
    min = anio;
    strcpy(mayor, nombre);
    strcpy(menor, nombre);

    while(!feof(pf)){
        fgets(cadena, TAM, pf);
    
        aux = strtok(cadena, "|");
        aux = strtok(NULL, "|");
        strcpy(nombre, aux);
        aux = strtok(NULL, "|");
        anio = atoi(aux);
        
        if(anio > min){
            strncpy(menor, nombre, sizeof(nombre));
            min = anio;
        }
        else if(anio < max){
            strncpy(mayor, nombre, sizeof(nombre));
            max = anio;
        }
    }
    printf("Mayor edad: %s\n", mayor);
    printf("Menor edad: %s\n", menor);
    
    fclose(pf);
    
    return 0;
}