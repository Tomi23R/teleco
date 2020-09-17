/**
 * Fichero : data_base.h      Fecha: 21/02/2018
 * Autores:                                   
 *                                            
 *  TAD para representar una base de datos de
 *  premios y premiadoes.
 *                                            
 */

#ifndef __DATA_BASE_H_
#define __DATA_BASE_H_

#include "premiado.h"
#include "premio.h"
#include "const.h"
#include "premios.h"
#include "list.h"

/* Estructura del TAD base de datos */
typedef struct _data_base data_base;
typedef struct _apariciones {
  premiado *p;
  premios *n_apariciones;
} apariciones;

/**
 * Funcion para crear una nueva base de datos, que 
 * contendrá los datos existentes en la raiz
 * pasada como parámetro.
 *
 * Entrada:
 *    Raiz de donde de los ficheros terminados en fpremiados.csv 
 *     (que contiene la informacion de los premiados) y fpremios.csv
 *     (que contiene los premios).
 *
 *      p.e. Si dirname es "datos/reducido_" entonces se debe abrir
 *           el fichero "datos/reducido_fpremiados.csv" para leer la
 *           info de los premiados y "datos/reducido_fpremios.csv"
 *           para los premios
 *
 * Salida:
 *    Una estructura data_base inicializada o NULL en caso de error
 */
data_base * new_data_base(const char *dirname);

/**
 * Funcion para liberar la memoria reservada y los recursos de la
 * base de datos.
 *
 * Entrada:
 *    Estructura data_base a liberar
 */
void destroy_data_base(data_base *db);

/**
 * Funcion para añadir un nuevo premio en la base de datos.
 * Comprueba que el premio no esté repetido (según su id, su 
 * clave primaria).
 * También se comprueba que todos los premiados del premio están
 * previamente añadidos a la base de datos.
 *
 * Entrada:
 *    La base de datos donde se añade y el premio a añadir.
 * Salida:
 *    Falso si el premio no se pudo añadir por no cumplir alguna restricción.
 */
BOOL data_base_add_premio(data_base *db, premio *f);

/**
 * Funcion para añadir un nuevo premiado en la base de datos.
 * Comprueba que no esté repetido (según su id, su 
 * clave primaria).
 *
 * Entrada:
 *    La base de datos donde se añade y el premio a añadir.
 * Salida:
 *    Falso si el premio está repetida y no se pudo añadir.
 */
BOOL data_base_add_premiado(data_base *db, premiado *a);

/**
 * Funcion para recuperar un premiado dado su id.
 *
 * Entrada:
 *    Estructura base de datos y el id del premiado a recuperar.
 *
 * Salida:
 *    Un puntero al premiado o NULL si no se encuentra.
 */
premiado * find_premiado_by_id(data_base * db, int id);
 
premiados* data_base_get_premiados(data_base* a);

premios* data_base_get_premios(data_base* a);

premio * find_premio_by_id(data_base * db, int id);

list * find_all_premiados(data_base *bd);

list * find_all_premios(data_base *bd);

list * find_premiado_by_nombre(data_base *bd, char *nombre);

list * find_premio_by_categoria(data_base *bd, char *cat);

list *find_apariciones_premiados(data_base *bd);

void print_apariciones(apariciones* a);

void destroy_apariciones(apariciones* a);

void data_base_make_index(data_base *db);

BOOL data_base_has_index(data_base *db);


#endif

