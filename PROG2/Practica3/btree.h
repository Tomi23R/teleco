/**
 * Fichero : btree.h      Fecha:16/02/2015
 * Autores:                                   
 *                                            
 *  fichero con la cabecera del TAD Arbol Binario de Busqueda
 *                                            
 */

#ifndef __BTREE_H_
#define __BTREE_H_

#include "list.h"

/*********************************************** Estructura del TAD arbol ***/
typedef struct _btree_node btree_node;
typedef struct _btree_node btree;

/**
 * Funcion para crear una nueva estructura de abdb que no hace nada
 *
 * Entrada:
 *
 * Salida:
 *    devuelve siempre NULL
 *
 * ATENCION: No teneis que implementar nada en esta funcion!!!!!
 */
btree* new_btree();

/**
 * Funcion para liberar la memoria reservada de la estructura abdb
 *
 * Entrada:
 *    Estructura arbol a liberar
 */
void destroy_btree(btree *abdb);

/**
 * Funcion para insertar un nodo en el arbol
 *
 * Entrada:
 *    Estructura arbol donde se inserta el nodo
 *    Cadena de caracteres con la clave de busqueda
 *    Void* con la info
 * Salida:
 *    El nodo del arbol con el nuevo nodo creado o NULL si da error
 */
btree* btree_insert_node(btree *t, const char* key, void* info);

/**
 * Funcion para recorrer el arbol en profundidad en orden
 *
 * Entrada:
 *    Estructura arbol a recorrer
 *    Lista donde se devuelven los elementos ordenados
 * Salida:
 *    Booleano indicando si todo ha ido bien o no
 */
BOOL btree_traverse(btree *abdb, list *resultado);

/**
 * Funcion para encontrar un elemento determinado en el arbol
 *
 * Entrada:
 *    Estructura arbol a recorrer
 *    String con la cadena a buscar
 * Salida:
 *    Void* con la info
 */
void* btree_find_element(btree *abdb, const char* search);

#endif

