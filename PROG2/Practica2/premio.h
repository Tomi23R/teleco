/**
 * Fichero : premio.h      Fecha:23/12/2014
 * Autores:                                   
 *                                            
 *  fichero con la cabecera del TAD premio
 *                                            
 */

#ifndef __PREMIO_H_
#define __PREMIO_H_

/*********************************************** Estructura del TAD premio ***/
typedef struct _premio premio;

#include "premiado.h"
#include "const.h"
#include "premiados.h"

/**
 * Funcion para crear una nueva estructura premio 
 *
 * Entrada:
 *
 * Salida:
 *    Una estructura premio inicializado todo a vacio o NULL en caso de error
 */
premio * new_premio();

/**
 * Funcion para liberar la memoria reservada de la estructura  TAD premio
 *
 * Entrada:
 *    Estructura premio a liberar
 */
void destroy_premio(premio * galardon);

/**
 * Funcion para asignar el id a un premio.
 *
 * Entrada:
 *    Estructura premio e id del premio
 *
 */
void set_premio_id(premio * galardon, int id);

/**
 * Funcion para asignar el categoria a un premio.
 *
 * Entrada:
 *    Estructura premio y categoria a asignar
 *
 */
void set_premio_categoria(premio * galardon, const char * categoria);

/**
 * Funcion para asignar el anio a un premio. No debe contener espacios
 *
 * Entrada:
 *    Estructura premio y el anio a asignar
 *
 */
void set_premio_anio(premio * galardon, int anio);

/**
 * Funcion para recuperar el id de un premio
 *
 * Entrada:
 *    Estructura premio sobre el que se quiere recuperar el id
 *
 * Salida:
 *    El id del premio
 */
int get_premio_id(premio * galardon);

/**
 * Funcion para recuperar el categoria de un premio
 *
 * Entrada:
 *    Estructura premio sobre el que se quiere recuperar el categoria
 *
 * Salida:
 *    El categoria del premio (es constante para que no se pueda modificar
 *        desde fuera)
 */
const char * get_premio_categoria(premio * galardon);

/**
 * Funcion para recuperar el anio de un premio
 *
 * Entrada:
 *    Estructura premio sobre el que se quiere recuperar el anio
 *
 * Salida:
 *    El anio del premio 
 */
int get_premio_anio(premio * galardon);

/**
 * Funcion para aniadir un premiado a un premio. 
 * No se comprueban duplicados (i.e., que el mismo premiado sea aniadido dos veces)
 *
 * Entrada:
 *    El premio y el premiado que se quiere aniadir.
 *
 * Salida:
 *    
 */
void add_premio_premiado(premio *galardon, premiado * t);

/**
 * Funcion que indica si un premiado es de un premio
 *
 * Entrada:
 *    El premio y el premiado que se quiere buscar.
 *
 * Salida:
 *  TRUE si a esta en galardon y FALSE en caso contrario
 *    
 */
BOOL has_premio_premiado(premio *galardon, premiado * t);

/**
 * Funcion para imprimir un premio por pantalla
 *
 * Entrada:
 *    Estructura del TAD premio a imprimir
 */
void print_premio(premio * galardon);

premiados* get_premiados_premio(premio* galardon);

#endif
