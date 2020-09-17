/**
 * Fichero : premiados.c      Fecha:23/12/2016
 * Autores:                                   
 *                                            
 *  fichero con la implementacion del array de premiados
 *                                            
 */

#include "premiados.h"
#include "const.h"

#include <stdlib.h>
#include <stdio.h>

/*********************************************** Estructura del TAD premiado ***/
struct _premiados {
  premiado **array_premiados;
  int n_premiados;
  int n_reserved;
  int last_id;
};

/**
 * Funcion para crear una nueva estructura premiado 
 *
 * Entrada:
 *
 * Salida:
 *    Una estructura premiados inicializado todo a vacio o NULL en caso de error
 */
premiados * new_premiados()
{
    /* (PRACTICA: a rellenar) */
    premiados* prem;
    
    prem = (premiados*)malloc(sizeof(premiados));
    
    if(!prem)
        return NULL;
        
    prem->n_premiados = 0;
    prem->n_reserved = 0;
    prem->last_id = NULL_ID;
    prem->array_premiados = NULL;
    
    return prem;
}

/**
 * Funcion para liberar la memoria reservada de la estructura premiados y todos los
 *   premiados que estan en el array.
 *
 * Entrada:
 *    Estructura premiados a liberar
 */
void destroy_premiados(premiados *tts)
{
    /* (PRACTICA: a rellenar) */
    if(!tts)
        return;
        
    if(tts->array_premiados != NULL)
        free(tts->array_premiados);
        
    free(tts);
}

/**
 * Funcion para aniadir un premiado ya creado al array 
 *
 * Entrada:
 *    Estructura del TAD premiados sobre el que se quiere aniadir un premiado y
 *    puntero al premiado a aniadir. Si el premiado ya existe no se intersara en
 *    la lista y se devolvera NULL_ID
 *
 * Salida:
 *    El id del premiado aniadido o NULL_ID  en caso de error
 */
long long int add_premiado(premiados * tts, premiado * t)
{
    /* (PRACTICA: a rellenar) */
    if(!tts)
        return NULL_ID;
    
    if(!t)
        return NULL_ID;
  
    if(get_premiado_by_id(tts, get_premiado_id(t)) != NULL)
        return NULL_ID;
    
    tts->n_premiados = (tts->n_premiados) + 1;
    tts->last_id = get_premiado_id(t);
    
    if(tts -> n_premiados == 1){
        tts->array_premiados = (premiado**)malloc(sizeof(premiado*));
    }
    else{
        tts->array_premiados = (premiado**)realloc(tts->array_premiados, tts->n_premiados * sizeof(premiado*));
    }
    
    tts->array_premiados[tts->n_premiados - 1] = t;
    
    return get_premiado_id(t);
}

/**
 * Funcion para recuperar el numero de premiados del array
 *
 * Entrada:
 *    Estructura del TAD premiados sobre el que se quiere recuperar su tamanio
 *
 * Salida:
 *    El numero de premiados
 */
int get_n_premiados(premiados * tts)
{
    /* (PRACTICA: a rellenar) */
    if (!tts)
        return -1;
    
    return tts->n_premiados;
}

/**
 * Funcion para recuperar el premiado n-esimo de la lista
 *
 * Entrada:
 *    Estructura premiados e indice del premiado a recuperar (indexado sobre 0)
 *
 * Salida:
 *    Un puntero al premiado o NULL si hay un error
 */
premiado * get_premiado_i(premiados * tts, int index)
{
    /* (PRACTICA: a rellenar) */
    if(!tts)
        return NULL;
    
    if(index >= tts->n_premiados || index < 0)
        return NULL;
        
    return tts->array_premiados[index];
}

/**
 * Funcion para recuperar un premiado dado su código.
 *
 * Entrada:
 *    Colección de premiados y el código del premiado a recuperar.
 *
 * Salida:
 *    Un puntero al premiado o NULL si no se encuentra.
 */
premiado * get_premiado_by_id(premiados *tts, long long int id)
{
    /* (PRACTICA: a rellenar) */
    int i;
    
    if(!tts)
        return NULL;
    
    for(i = 0; i < tts->n_premiados; i++){
        if(get_premiado_id(tts->array_premiados[i]) == id)
            return tts->array_premiados[i];
    }
    return NULL;
}


/**
 * Funcion para imprimir la lista de premiados por pantalla
 *
 * Entrada:
 *    Estructura TAD premiado a imprimir
 */
void print_premiados(premiados *tts) 
{
    /* (PRACTICA: a rellenar) */
    int i;
    if(!tts)
        return;
    printf("\tPREMIADOS:\n");
    printf("\tNUMERO DE PREMIADOS: %d\n", tts->n_premiados);
    printf("\tLISTADO DE PREMIADOS\n");
    
    for(i = 0; i < tts->n_premiados; i++){
        print_premiado(tts->array_premiados[i]);
    }
    
    printf("\n\tN_RESERVED: %d\n", tts->n_reserved);
    printf("\tLAST ID: %d\n", tts->last_id);
}


