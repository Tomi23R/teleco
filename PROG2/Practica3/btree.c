/**
 * Fichero : btree.c      Fecha:16/02/2018
 * Autores:                                   
 *                                            
 *  fichero con la cabecera del TAD Arbol Binario de Busqueda
 *                                            
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "btree.h"
#include "list.h"
#include "const.h"

/*********************************************** Estructura del TAD arbol ***/
struct _btree_node {
  char * clave;
  void * info;
  struct _btree_node * izq;
  struct _btree_node * dch;
}; 

/**
 * Funcion para crear una nueva estructura de abdb
 *
 * Entrada:
 *
 * Salida:
 *    devuelve siempre NULL
 *
 * ATENCION: No teneis que implementar nada en esta funcion!!!!!
 */
btree * new_btree()
{
  return NULL;
}

/**
 * Funcion para crear una nueva estructura de abdb
 *
 * Entrada:
 *
 * Salida:
 *    devuelve el nodo del arbol inicializado o NULL
 *    si hay algun error
 *
 */
btree * new_btree_node(const char *key, void * info)
{
  btree* arbol;
    
  arbol = (btree*)malloc(sizeof(btree));
  
  arbol->info = info;
  arbol->clave = (char*)malloc(strlen(key) + 1);
  strcpy(arbol->clave, key);
  
  arbol->izq = NULL;
  arbol->dch = NULL;
  
  return arbol;
}

/**
 * Funcion para liberar la memoria reservada de la estructura abdb
 *
 * Entrada:
 *    Estructura arbol a liberar
 */
void destroy_btree(btree *abdb)
{
  if(!abdb)
    return;
    
  if(abdb->clave != NULL){
    free(abdb->clave);
  }
  
  destroy_btree(abdb->izq);
  destroy_btree(abdb->dch);
  free(abdb);
}

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
btree *btree_insert_node(btree *t, const char* key, void* info)
{
  int cmp;

  
  if (t==NULL) {
    /* Si t es NULL se crea un nuevo nodo y se devuelve */
    return new_btree_node(key, info);
  }

  cmp = strcmp(key, t->clave);
  if (cmp==0) { 
    /* Ya existe un nodeo con esa clave. Se actualiza la informacion
       y se devuelve */
    t->info = info;
    return t;
  }
  else if (cmp<0) {
    t->izq = btree_insert_node(t->izq, key, info);
  }
  else {
    t->dch = btree_insert_node(t->dch, key, info);
  }

  return t;
}

/**
 * Funcion para recorrer el arbol en profundidad en orden
 *
 * Entrada:
 *    Estructura arbol a recorrer
 *    Lista donde se devuelven los elementos ordenados
 * Salida:
 *    Booleano indicando si todo ha ido bien o no
 */
BOOL btree_traverse(btree *t, list *resultado)
{
  if(!resultado || !t)
    return FALSE;
    
  btree_traverse(t->dch, resultado);
  list_insert(resultado, t->info);
  btree_traverse(t->izq, resultado);
  
  return TRUE;
}


/**
 * Funcion para encontrar un elemento determinado en el arbol
 *
 * Entrada:
 *    Estructura arbol a recorrer
 *    String con la cadena a buscar
 * Salida:
 *    Void* con la info
 */
void* btree_find_element(btree *t, const char* search)
{
  int cmp;
  
  if(!t || !search)
    return NULL;
    
  cmp = strcmp(t->clave, search);
  
  if(cmp > 0){
    return btree_find_element(t->izq, search);
  }
  else if(cmp < 0){
    return btree_find_element(t->dch, search);
  }
  else{
    return t->info;
  }
}

