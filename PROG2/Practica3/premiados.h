/**
 * Fichero : premiados.h      Fecha:23/12/2014
 * Autores:                                   
 *                                            
 *  fichero con la cabecera del TAD premiados
 *                                            
 */

/*#include "premio.h"*/

#ifndef __PREMIADOS_H_
#define __PREMIADOS_H_

#include "premiado.h"

/*********************************************** Estructura del TAD premiados ***/
typedef struct _premiados premiados;

/**
 * Funcion para crear una nueva estructura premiado 
 *
 * Entrada:
 *
 * Salida:
 *    Una estructura premiados inicializado todo a vacio o NULL en caso de error
 */
premiados * new_premiados();

/**
 * Funcion para liberar la memoria reservada de la estructura premiados y todos los
 *   premiadoes que estan en el array.
 *
 * Entrada:
 *    Estructura premiados a liberar
 */
void destroy_premiados(premiados *tts);

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
long long int add_premiado(premiados * tts, premiado * user);

/**
 * Funcion para recuperar el numero de premiadoes del array
 *
 * Entrada:
 *    Estructura del TAD premiados sobre el que se quiere recuperar su tamanio
 *
 * Salida:
 *    El numero de premiadoes
 */
int get_n_premiados(premiados * tts);

/**
 * Funcion para recuperar el premiado n-esimo de la lista
 *
 * Entrada:
 *    Estructura premiados e indice del premiado a recuperar (indexado sobre 0)
 *
 * Salida:
 *    Un puntero al premiado o NULL si hay un error
 */
premiado * get_premiado_i(premiados * tts, int index);


/**
 * Funcion para recuperar un premiado dado su código.
 *
 * Entrada:
 *    Colección de premiadoes y el código del premiado a recuperar.
 *
 * Salida:
 *    Un puntero al premiado o NULL si no se encuentra.
 */
premiado * get_premiado_by_id(premiados *tts, long long int id);

/**
 * Funcion para imprimir la lista de premiadoes por pantalla
 *
 * Entrada:
 *    Estructura TAD premio a imprimir
 */
void print_premiados(premiados *tts); 

#endif

