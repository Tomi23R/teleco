/**
 * Fichero : premios.h      Fecha:23/12/2014
 * Autores:                                   
 *                                            
 *  fichero con la cabecera del TAD premios
 *                                            
 */

/*#include "premio.h"*/

#ifndef __PREMIOS_H_
#define __PREMIOS_H_

#include "premio.h"

/*********************************************** Estructura del TAD premios ***/
typedef struct _premios premios;

/**
 * Funcion para crear una nueva estructura premio 
 *
 * Entrada:
 *
 * Salida:
 *    Una estructura premios inicializado todo a vacio o NULL en caso de error
 */
premios * new_premios();

/**
 * Funcion para liberar la memoria reservada de la estructura premios y todos los
 *   premios que estan en el array.
 *
 * Entrada:
 *    Estructura premios a liberar
 */
void destroy_premios(premios *galardones);

/**
 * Funcion para aniadir un premio ya creado al array. No se pueden
 * repetir los ids. Si ya exite el id se devuelve NULL_ID
 *
 * Entrada:
 *    Estructura del TAD premios sobre el que se quiere aniadir un premio y
 *    puntero al premio a aniadir. 
 *
 * Salida:
 *    El id del premio aniadido o NULL_ID en caso de error 
 */
long long int add_premio(premios * galardones, premio * t);

/**
 * Funcion para recuperar el numero de premios del array
 *
 * Entrada:
 *    Estructura del TAD premios sobre el que se quiere recuperar su tamanio
 *
 * Salida:
 *    El numero de premios
 */
int get_n_premios(premios * galardones);

/**
 * Funcion para recuperar el premio n-esimo de la lista
 *
 * Entrada:
 *    Estructura premios e indice del premio a recuperar (indexado sobre 0)
 *
 * Salida:
 *    Un puntero al premio o NULL si hay un error
 */
premio * get_premio_i(premios *galardones, int index);


/**
 * Funcion para recuperar un premio dado su código.
 *
 * Entrada:
 *    Colección de premios y el código del premio a recuperar.
 *
 * Salida:
 *    Un puntero al premio o NULL si no se encuentra.
 */
premio * get_premio_by_id(premios *galardones, int id);

/**
 * Funcion para imprimir la lista de premios por pantalla
 *
 * Entrada:
 *    Estructura TAD premio a imprimir
 */
void print_premios(premios *galardones); 

#endif

