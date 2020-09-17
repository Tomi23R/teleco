/**
 * Fichero : premio.c      Fecha:23/12/2016
 * Autores:                                   
 *                                            
 *  fichero con la implementacion del TAD premio
 *                                            
 */

#include "premio.h"
#include "premiados.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


/*********************************************** Estructura del TAD premio ***/
struct _premio {
  int id;
  char * categoria;
  int anio;
  premiados * mis_premiados; /* premiados */
};

/**
 * Funcion para crear una nueva estructura premio 
 *
 * Entrada:
 *
 * Salida:
 *    Una estructura premio inicializado todo a vacio o NULL en caso de error
 */
premio * new_premio()
{
    /* (PRACTICA: a rellenar) */
    premio* prem;
    
    prem = (premio*)malloc(sizeof(premio));
    
    if(!prem)
        return NULL;
        
    prem->id = NULL_ID;
    prem->categoria = NULL;
    prem->anio = NULL_ID;
    prem->mis_premiados = new_premiados();
    
    return prem;
}

/**
 * Funcion para liberar la memoria reservada de la estructura premio
 *
 * Entrada:
 *    Estructura premio a liberar
 */
void destroy_premio(premio *galardon)
{
    /* (PRACTICA: a rellenar) */
    if(!galardon)
        return;
    
    if(galardon->categoria != NULL)
        free(galardon->categoria);
    
    if(galardon->mis_premiados != NULL)
        destroy_premiados(galardon->mis_premiados);
    
    free(galardon);
}

/**
 * Funcion para asignar el id a un premio.
 *
 * Entrada:
 *    Estructura premio e id del mismo
 *
 */
void set_premio_id(premio * galardon, int id)
{
    /* (PRACTICA: a rellenar) */
    if(!galardon)
        return;
    
    galardon->id = id;
}

/**
 * Funcion para asignar el categoria a un premio
 *
 * Entrada:
 *    Estructura premio y el categoria
 *
 */
void set_premio_categoria(premio * galardon, const char *categoria)
{
    /* (PRACTICA: a rellenar) */
    char* aux;
    
    if(!galardon)
        return;
        
    if(!categoria)
        return;
    
    if(galardon->categoria != NULL)
        free(galardon->categoria);
        
    aux = (char*)malloc(strlen(categoria)*sizeof(char) + 1);
    
    strcpy(aux, categoria);
    
    galardon->categoria = aux;
}

/**
 * Funcion para asignar el anio a un premio
 *
 * Entrada:
 *    Estructura premio y el anio
 *
 */
void set_premio_anio(premio * galardon, int anio)
{
    /* (PRACTICA: a rellenar) */
    if(!galardon)
        return;
    
    galardon->anio = anio;
}

/**
 * Funcion para recuperar el id de un premio
 *
 * Entrada:
 *    Estructura premio sobre la que se quiere recuperar el id
 *
 * Salida:
 *    El id
 */
int get_premio_id(premio * galardon)
{
    /* (PRACTICA: a rellenar) */
    if(!galardon)
        return -1;
    
    return galardon->id;
}

/**
 * Funcion para recuperar el categoria de un premio
 *
 * Entrada:
 *    Estructura premio sobre el que se quiere recuperar el categoria
 *
 * Salida:
 *    El categoria del premio  (es constante para que no se pueda modificar
 *        desde fuera)
 */
const char * get_premio_categoria(premio * galardon)
{
    /* (PRACTICA: a rellenar) */
    if(!galardon)
        return NULL;
    
    if(!galardon->categoria)
        return NULL;
    
    return galardon->categoria;
}

/**
 * Funcion para recuperar el anio de un premio
 *
 * Entrada:
 *    Estructura premio sobre el que se quiere recuperar el anio
 *
 * Salida:
 *    El anio del premio 
 */
int get_premio_anio(premio * galardon)
{
    /* (PRACTICA: a rellenar) */
    if(!galardon)
        return -1;
        
    return galardon->anio;
}


/**
 * Funcion para añadir un premiado a un premio 
 * No se comprueban duplicados (i.e., que el mismo premiado sea aniadido dos veces)
 *
 * Entrada:
 *    El premio y el premiado que se quiere aniadir.
 *
 * Salida:
 *    
 */
void add_premio_premiado(premio *galardon, premiado *t)
{
    /* (PRACTICA: a rellenar) */
    if(!galardon)
        return;
        
    if(!t)
        return;
        
    add_premiado(galardon->mis_premiados, t);
}

/**
 * Funcion que indica si un premiado pertenece al premio 
 *
 * Entrada:
 *    El premio y el premiado que se quiere buscar.
 *
 * Salida:
 *  TRUE si a esta en galardon y FALSE en caso contrario
 *    
 */
BOOL has_premio_premiado(premio *galardon, premiado *t)
{
    /* (PRACTICA: a rellenar) */
    if(!galardon)
        return FALSE;
    
    if(!t) 
        return FALSE;
        
    if(!galardon->mis_premiados)
        return FALSE;
        
    if(get_premiado_by_id(galardon->mis_premiados, get_premiado_id(t)) != NULL)
        return TRUE;
    
    return FALSE;
}

/**
 * Funcion para imprimir la estructura premio por pantalla
 *
 * Entrada:
 *    Estructura premio a imprimir
 */
void print_premio(premio *galardon) 
{
    /* (PRACTICA: a rellenar) */
    if(!galardon)
        return;
    printf("PREMIO:\n");
    printf("\tID: %d\n",galardon->id);
    if(galardon->categoria != NULL)
        printf("\tCATEGORIA: %s", galardon->categoria);
        
    printf("\tANIO: %d\n", galardon->anio);
    if(galardon->mis_premiados != NULL)
        print_premiados(galardon->mis_premiados);
}

premiados* get_premiados_premio(premio* galardon){
    if(!galardon)
        return NULL;
    
    return galardon->mis_premiados;
}


