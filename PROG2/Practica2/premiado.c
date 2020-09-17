/**
 * Fichero : premiado.c      Fecha:23/12/2016
 * Autores:                                   
 *                                            
 *  fichero con la implementacion del TAD premiado
 *                                            
 */

#include "premiado.h"
#include "const.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*********************************************** Estructura del TAD premiado ***/
struct _premiado {
  int id;
  char * nombre;
  char * pais;
  GENERO genero;
};


/**
 * Funcion para crear una nueva estructura premiado 
 *
 * Entrada:
 *
 * Salida:
 *    Una estructura premiado inicializado todo a vacio o NULL en caso de error
 */
premiado * new_premiado()
{
    /* (PRACTICA: a rellenar) */
    premiado* prem;
    prem = (premiado*)malloc(sizeof(premiado));
    
    if(!prem)
        return NULL;
        
    prem->id = NULL_ID;
    prem->nombre = NULL;
    prem->pais = NULL;
    prem->genero = NO_DEFINIDO;
    
    return prem;
}

/**
 * Funcion para liberar la memoria reservada de la estructura premiado
 *
 * Entrada:
 *    Estructura premiado a liberar
 */
void destroy_premiado(premiado *t)
{
    if(!t)
        return;
    
    if(t->nombre != NULL)
        free(t->nombre);
        
    if(t->pais != NULL)
        free(t->pais);
        
    free(t);
}

/**
 * Funcion para establecer el identificador del premiado.
 *
 * Entrada:
 *    Estructura premiado e id del premiado
 *
 */
void set_premiado_id(premiado * t, int id)
{
    /* (PRACTICA: a rellenar) */
    if(!t)
        return;
        
    t->id = id;
}

/**
 * Funcion para establecer el nombreo del premiado.
 *
 * OJO: Esta función debe hacer una copia de la cadena que se pasa
 *
 * Entrada:
 *    Estructura premiado y el nombreo del premiado
 *
 */
void set_premiado_nombre(premiado * t, const char * nombre)
{
    /* (PRACTICA: a rellenar) */
    char *aux;
    
    if(!t)
        return;
    
    if(!nombre)
        return;
        
    if(t->nombre != NULL)
        free(t->nombre);
        
    aux = (char*)malloc(strlen(nombre)*sizeof(char) + 1);
    strcpy(aux,nombre);
    t->nombre = aux;
}

/**
 * Funcion para establecer el autor del premiado.
 *
 * Entrada:
 *    Estructura premiado e autor del premiado
 *
 */
void set_premiado_pais(premiado * t, const char *pais)
{
    /* (PRACTICA: a rellenar) */
    char *aux;
    
    if(!t)
        return;
    
    if(!pais)
        return;
    
    if(t->pais != NULL)
        free(t->pais);
        
    aux = (char*)malloc(strlen(pais)*sizeof(char) + 1);
    strcpy(aux,pais);
    t->pais = aux;
}
/**
 * Funcion para establecer el genero del premiado.
 *
 * Entrada:
 *    Estructura del TAD premiado y el valor del enumerado genero.
 *
 * Salida:
 */
void set_premiado_genero(premiado * t, GENERO genero)
{
    /* (PRACTICA: a rellenar) */
    if(!t)
        return;
        
    t->genero = genero;
}


/**
 * Funcion para recuperar el id de un premiado
 *
 * Entrada:
 *    Estructura del TAD premiado sobre el que se quiere recuperar el id
 *
 * Salida:
 *    El id del premiado
 */
int get_premiado_id(premiado * t)
{
    /* (PRACTICA: a rellenar) */
    if(!t)
        return -1;
    
    return t->id;
}

/**
 * Funcion para recuperar el nombreo de un premiado
 *
 * Entrada:
 *    Estructura del TAD premiado sobre el que se quiere recuperar el nombre
 *
 * Salida:
 *    El nombre del premiado (es constante para que no se pueda modificar
 *        desde fuera)
 */
const char * get_premiado_nombre(premiado * t)
{  
    /* (PRACTICA: a rellenar) */
    if(!t)
        return NULL;
    
    if(!t->nombre)
        return NULL;
    
    return t->nombre;
}

/**
 * Funcion para recuperar el pais de un premiado
 *
 * Entrada:
 *    Estructura del TAD premiado sobre el que se quiere recuperar el autor
 *
 * Salida:
 *    El pais del premiado (es constante para que no se pueda modificar
 *        desde fuera)
 */
const char *get_premiado_pais(premiado * t)
{
    /* (PRACTICA: a rellenar) */
    if(!t)
        return NULL;
        
    if(!t->pais)
        return NULL;
    
    return t->pais;
}
/**
 * Funcion para recuperar el genero de un premiado
 *
 * Entrada:
 *    Estructura del TAD premiado sobre el que se quiere recuperar el genero
 *
 * Salida:
 *    El genero del premiado
 */
GENERO get_premiado_genero(premiado * t)
{
    /* (PRACTICA: a rellenar) */
    if(!t)
        return NO_DEFINIDO;
        
    return t->genero;
}


/**
 * Funcion para imprimir un premiado por pantalla
 *
 * Entrada:
 *    Estructura TAD premiado a imprimir
 */
void print_premiado(premiado *t) 
{
    /* (PRACTICA: a rellenar) */
    if(!t)
        return;
    
    printf("\n\t\tPREMIADO:\n");
    printf("\t\tID: %d\n",t->id);
    if(t->nombre != NULL)
        printf("\t\tNOMBRE: %s\n", t->nombre);
        
    if(t->pais != NULL)
        printf("\t\tPAIS: %s\n", t->pais);
        
    if(t->genero == HOMBRE)
        printf("\t\tGENERO: hombre\n");
    else if(t->genero == MUJER)
        printf("\t\tGENERO: mujer\n");
    else if(t->genero == ORGANISMO)
        printf("\t\tGENERO: organismo\n");
    else
        printf("\t\tGENERO: no definido\n");
}


