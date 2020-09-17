/**
 * Fichero : premiado.h      Fecha:23/12/2014
 * Autores:                                   
 *                                            
 *  fichero con la cabecera del TAD premiado
 *                                            
 */


#ifndef __PREMIADO_H_
#define __PREMIADO_H_

typedef enum {HOMBRE, MUJER, ORGANISMO, NO_DEFINIDO} GENERO;

/*********************************************** Estructura del TAD premiado ***/
typedef struct _premiado premiado;

/**
 * Funcion para crear una nueva estructura premiado 
 *
 * Entrada:
 *
 * Salida:
 *    Una estructura premiado inicializado todo a vacio o NULL en caso de error
 */
premiado * new_premiado();

/**
 * Funcion para liberar la memoria reservada de la estructura premiado
 *
 * Entrada:
 *    Estructura premiado a liberar
 */
void destroy_premiado(premiado *t);

/**
 * Funcion para establecer el identificador del premiado.
 *
 * Entrada:
 *    Estructura del TAD premiado y el identificador como un entero.
 *
 * Salida:
 */
void set_premiado_id(premiado * t, int id);

/**
 * Funcion para establecer el nombre del premiado.
 *
 * OJO: Esta función debe hacer una copia de la cadena que se pasa
 *
 * Entrada:
 *    Estructura del TAD premiado y el nombre del premiado.
 *
 * Salida:
 */
void set_premiado_nombre(premiado * t, const char * nombre);

/**
 * Funcion para establecer el pais del premiado.
 *
 * OJO: Esta función debe hacer una copia de la cadena que se pasa
 *
 * Entrada:
 *    Estructura del TAD premiado y el pais del premiado.
 *
 * Salida:
 */
void set_premiado_pais(premiado * t, const char * pais);

/**
 * Funcion para establecer el genero del premiado.
 *
 * Entrada:
 *    Estructura del TAD premiado y el valor del enumerado genero.
 *
 * Salida:
 */
void set_premiado_genero(premiado * t, GENERO genero);

/**
 * Funcion para recuperar el id de un premiado
 *
 * Entrada:
 *    Estructura del TAD premiado sobre el que se quiere recuperar el id
 *
 * Salida:
 *    El id del premiado
 */
int get_premiado_id(premiado * t);

/**
 * Funcion para recuperar el nombre de un premiado
 *
 * Entrada:
 *    Estructura del TAD premiado sobre el que se quiere recuperar el nombre
 *
 * Salida:
 *    El nombre del premiado (es constante para que no se pueda modificar
 *        desde fuera)
 */
const char * get_premiado_nombre(premiado * t);

/**
 * Funcion para recuperar el pais de un premiado
 *
 * Entrada:
 *    Estructura del TAD premiado sobre el que se quiere recuperar el pais
 *
 * Salida:
 *    El pais del premiado (es constante para que no se pueda modificar
 *        desde fuera)
 */
const char *get_premiado_pais(premiado * t);

/**
 * Funcion para recuperar el genero de un premiado
 *
 * Entrada:
 *    Estructura del TAD premiado sobre el que se quiere recuperar el genero
 *
 * Salida:
 *    El genero del premiado
 */
GENERO get_premiado_genero(premiado * t);

/**
 * Funcion para imprimir un premiado por pantalla
 *
 * Entrada:
 *    Estructura TAD premiado a imprimir
 */
void print_premiado(premiado *t);

#endif

