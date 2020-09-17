/**
 * Fichero : premios.c      Fecha:23/12/2016
 * Autores:                                   
 *                                            
 *  fichero con la implementacion del array de premios
 *                                            
 */

#include "premios.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

/*********************************************** Estructura del TAD premio ***/
struct _premios {
  premio **array_premios;
  int n_premios;
  int n_reserved;
};


/**
 * Funcion para crear una nueva estructura premios
 *
 * Entrada:
 *
 * Salida:
 *    Una estructura premios inicializado todo a vacio o NULL en caso de error
 */
premios * new_premios()
{
    /* (PRACTICA: a rellenar) */
    premios* prem;
    
    prem = (premios*)malloc(sizeof(premios));
    
    if(!prem)
        return NULL;
    
    prem ->n_premios = 0;
    prem->n_reserved = 0;
    prem->array_premios = NULL;
    
    return prem;
}

/**
 * Funcion para liberar la memoria reservada de la estructura premios 
 *   OJO: No se debe liberar la memoria de los premios del array pero si el 
 *        array
 *
 * Entrada:
 *    Estructura premios a liberar
 */
void destroy_premios(premios *galardones)
{
    /* (PRACTICA: a rellenar) */
    if(!galardones)
        return;
        
    if(galardones->array_premios != NULL)
        free(galardones->array_premios);
        
    free(galardones);
    
}

/**
 * Funcion para aniadir un premio ya creado al array. Si el id ya existe
 *   no se puede aniadir el premio. En cuyo caso se devuelve NULL_ID
 *
 * Entrada:
 *    Estructura del TAD premios sobre el que se quiere aniadir un premio y
 *    puntero al premio a aniadir. 
 *
 * Salida:
 *    El id del premio aniadido o NULL_ID en caso de error 
 */
long long int add_premio(premios * galardones, premio * user)
{
    /* (PRACTICA: a rellenar) */
    if(!galardones)
        return NULL_ID;
    
    if(!user)
        return NULL_ID;
    
    if(get_premio_id(user) == NULL_ID)
        return NULL_ID;
  
    if(get_premio_by_id(galardones, get_premio_id(user)) != NULL)
        return NULL_ID;
    
    galardones->n_premios = (galardones->n_premios) + 1;
    
    if(galardones -> n_premios == 1){
        galardones->array_premios = (premio**)malloc(sizeof(premio*));
    }
    else{
        galardones->array_premios = (premio**)realloc(galardones->array_premios, galardones->n_premios* sizeof(premio*));
    }
    
    galardones->array_premios[galardones->n_premios - 1] = user;
    
    return get_premio_id(user);
}

/**
 * Funcion para recuperar el numero de premios del array
 *
 * Entrada:
 *    Estructura del TAD premios sobre el que se quiere recuperar su tamanio
 *
 * Salida:
 *    El numero de premios
 */
int get_n_premios(premios * galardones)
{
    /* (PRACTICA: a rellenar) */
    if(!galardones)
        return -1;

    return galardones->n_premios;
}

/**
 * Funcion para recuperar el premio n-esimo de la lista
 *
 * Entrada:
 *    Estructura premios e indice del premio a recuperar (indexado sobre 0)
 *
 * Salida:
 *    Un puntero al premio o NULL si hay un error
 */
premio * get_premio_i(premios * galardones, int index)
{
    /* (PRACTICA: a rellenar) */
    if(!galardones)
        return NULL;
    
    if(index >= galardones->n_premios || index < 0)
        return NULL;
        
    return galardones->array_premios[index];
}

/**
 * Funcion para recuperar un premio dado su código.
 *
 * Entrada:
 *    Colección de premios y el código del premio a recuperar.
 *
 * Salida:
 *    Un puntero al premio o NULL si no se encuentra.
 */
premio * get_premio_by_id(premios *tts, int id)
{
    /* (PRACTICA: a rellenar) */
    int i;
    
    if(!tts)
        return NULL;
    
    for(i = 0; i < tts->n_premios; i++){
        if(get_premio_id(tts->array_premios[i]) == id)
            return tts->array_premios[i];
    }
    return NULL;
}

/**
 * Funcion para imprimir la lista de premios por pantalla
 *
 * Entrada:
 *    Estructura TAD premio a imprimir
 */
void print_premios(premios *galardones) 
{
    /* (PRACTICA: a rellenar) */
    int i;
    
    if(!galardones)
        return;
    
    printf("PREMIOS:\n");
    printf("NUMERO DE PREMIOS: %d\n", galardones->n_premios);
    printf("LISTADO DE PREMIOS\n");
    
    for(i = 0; i < galardones->n_premios; i++){
        print_premio(galardones->array_premios[i]);
    }
    
    printf("\nN_RESERVED: %d\n", galardones->n_reserved);
}


