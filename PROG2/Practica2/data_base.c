/**
 * Fichero : data_base.c      Fecha:21/02/2018
 * Autores:                                   
 *                                            
 *  Implementación del TAD Base de Datos.
 *                                            
 */

#include "data_base.h"

#include "premiados.h"
#include "premios.h"
#include "premiado.h"
#include "premio.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>


#define PREMIOS_FILE   "fpremios.csv"
#define PREMIADOS_FILE  "fpremiados.csv"

/* Estructura del TAD data_base */
struct _data_base {
  premiados * table_premiados;
  premios * table_premios;
};


/**
 *  Funciones auxiliares
 *
 */
char * create_path(const char *dirname, const char *filename);
premiados * bd_parse_file_premiados(char * file_name);
premiado * bd_parse_premiado(char * registro);
premios * bd_parse_file_premios(char * file_name, premiados * aa);
premio * bd_parse_premio(char * registro, premiados * aa);

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
 *   Se puede implementar la funcion create_path como apoyo para
 *   crear las rutas a los ficheros
 *
 * Salida:
 *    Una estructura data_base inicializada o NULL en caso de error
 */
data_base * new_data_base(const char *dirname)
{
    /* (PRACTICA: a rellenar) */
    data_base* data;
    char* aux;
    
    if(!dirname)
        return NULL;
    
    data = (data_base*)malloc(sizeof(data_base));
    
    aux = create_path(dirname, PREMIADOS_FILE);
    
    data->table_premiados = bd_parse_file_premiados(aux);
    
    free(aux);
    
     if(data->table_premiados == NULL){
        destroy_data_base(data);
        return NULL;
     }
    
    aux = create_path(dirname, PREMIOS_FILE);
    
    data->table_premios = bd_parse_file_premios(aux, data->table_premiados);
    
    free(aux);
    
    if(data->table_premios == NULL){
        destroy_data_base(data);
        return NULL;
    }
    
    return data;
}

/**
 * Funcion para liberar la memoria reservada y los recursos de la
 * base de datos.
 *
 * Entrada:
 *    Estructura data_base a liberar
 */
void destroy_data_base(data_base *db)
{   
    int i;
    /* (PRACTICA: a rellenar) */
    if(!db)
        return;
        
    for(i = 0; i < get_n_premios(db->table_premios); i++){
        destroy_premio(get_premio_i(db->table_premios, i));
    }
    destroy_premios(db->table_premios);
    for(i = 0; i< get_n_premiados(db->table_premiados); i++){
        destroy_premiado(get_premiado_i(db->table_premiados, i));
    }
    destroy_premiados(db->table_premiados);
    free(db);
}


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
BOOL data_base_add_premio(data_base *db, premio *f)
{
    int i;
    premiados* aux;
    /* (PRACTICA: a rellenar) */
    if(!db)
        return FALSE;
    
    if(!f)
        return FALSE;
    aux = get_premiados_premio(f);
    /*Comprobar que los premiados que han obtenido el premio estan en la base de datos*/
    for(i = 0; i < get_n_premiados(aux); i++){
        if(find_premiado_by_id(db, get_premiado_id(get_premiado_i(aux, i))) == NULL)
            return FALSE;
    }
    if(find_premio_by_id(db, get_premio_id(f)) == NULL){
        add_premio(db->table_premios, f);
        return TRUE;
    }
    return FALSE;
}

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
BOOL data_base_add_premiado(data_base *db, premiado *a)
{  
    /* (PRACTICA: a rellenar) */
    if(!db)
        return FALSE;
    
    if(!a)
        return FALSE;
        
    if(find_premiado_by_id(db, get_premiado_id(a)) == NULL){
        add_premiado(db->table_premiados,a);
        return TRUE;
    }
    return FALSE;
}


/********** Funciones de consulta ************/

/**
 * Funcion para recuperar un premiado dado su id.
 *
 * Entrada:
 *    Estructura base de datos y el id del premiado a recuperar.
 *
 * Salida:
 *    Un puntero al premiado o NULL si no se encuentra.
 */
premiado * find_premiado_by_id(data_base * db, int id)
{
    /* (PRACTICA: a rellenar) */
    if(!db)
        return NULL;
    
    return get_premiado_by_id(db->table_premiados, id);
}

/**
 * Funcion para recuperar una premio dado su id.
 *
 * Entrada:
 *    Estructura base de datos y el id de el premio a recuperar.
 *
 * Salida:
 *    Un puntero a el premio o NULL si no se encuentra.
 */
premio * find_premio_by_id(data_base * db, int id)
{
    /* (PRACTICA: a rellenar) */
    if(!db)
        return NULL;
        
    return get_premio_by_id(db->table_premios, id);
}

char * create_path(const char *dirname, const char *filename){
    char* aux;
    
    if(!dirname)
        return NULL;
    
    if(!filename)
        return NULL;
    
    aux = (char*)malloc(100);    
    strcpy(aux,dirname);
    strcat(aux,filename);
    
    return aux;
}

premiados * bd_parse_file_premiados(char * file_name){
    premiados* galardonados;
    premiado* galardonado;
    FILE* pf;
    char aux[500];
    
    if(!file_name)
        return NULL;
        
    pf = fopen(file_name, "r");
    
    if(!pf)
        return NULL;
        
    galardonados = new_premiados();
    
    while(!feof(pf)){
        bzero(aux,500);
        fgets(aux,500,pf);
        galardonado = bd_parse_premiado(aux);
        add_premiado(galardonados,galardonado);
    }
    
    fclose(pf);
    return galardonados;
}

premiado * bd_parse_premiado(char * registro){
    premiado* galardonado;
    char* toks;
    
    if(!registro)
        return NULL;
        
    galardonado = new_premiado();
    toks = strtok(registro, ",");
    set_premiado_id(galardonado, atoi(toks));
    toks = strtok(NULL,",");
    set_premiado_nombre(galardonado, toks);
    toks = strtok(NULL,",");
    set_premiado_pais(galardonado,toks);
    toks = strtok(NULL,",");
    toks = strtok(toks,"\n");
    if(strcmp(toks, "male") == 0){
        set_premiado_genero(galardonado,HOMBRE);
    }else if(strcmp(toks, "female") == 0){
        set_premiado_genero(galardonado, MUJER);
    }else if(strcmp(toks, "org") == 0){
        set_premiado_genero(galardonado, ORGANISMO);
    }else{
        set_premiado_genero(galardonado, NO_DEFINIDO);
    }
    return galardonado;
}

premios * bd_parse_file_premios(char * file_name, premiados * aa){
    premios* galardones;
    FILE* pf;
    premio* galardon;
    
    char aux[500];
    
    if(!file_name)
        return NULL;
    
    if(!aa)
        return NULL;
        
    pf = fopen(file_name, "r");
    
    if(!pf)
        return NULL;
    
    galardones = new_premios();
    
    while(!feof(pf)){
        bzero(aux,500);
        fgets(aux,500,pf);
        galardon = bd_parse_premio(aux, aa);
        add_premio(galardones, galardon);
    }
    fclose(pf);
    
    return galardones;
}

premio * bd_parse_premio(char * registro, premiados * aa){
    premio* galardon;
    premiado* galardonado;
    char* toks;
    
    if(!registro)
        return NULL;
        
    if(!aa)
        return NULL;
        
    galardon = new_premio();
    
    toks = strtok(registro,",");
    set_premio_id(galardon, atoi(toks));
    toks = strtok(NULL,",");
    set_premio_anio(galardon, atoi(toks));
    toks = strtok(NULL,",");
    set_premio_categoria(galardon, toks);
    /*No hay campo descripcion en premio*/
    toks = strtok(NULL,",");
    toks = strtok(NULL,"|");
    do{
        galardonado = get_premiado_by_id(aa, atoi(toks));
        add_premio_premiado(galardon, galardonado);
        toks = strtok(NULL,"|");
    }while(toks != NULL);
    
    return galardon;
}

premiados* data_base_get_premiados(data_base* a){
    return a->table_premiados;
}

premios* data_base_get_premios(data_base* a){
    return a->table_premios;
}

list * find_all_premiados(data_base *bd){
    list* lista;
    premiado* galardonado;
    int i;
    
    if(!bd)
        return NULL;
    
    lista = new_list();
    
    for(i = 0; i < get_n_premiados(bd->table_premiados); i++){
        galardonado = get_premiado_i(bd->table_premiados, i);
        list_insert(lista, galardonado);
    }
    
    return lista;
}

list * find_all_premios(data_base *bd){
    list* lista;
    premio* galardon;
    int i;
    
    if(!bd)
        return NULL;
    
    lista = new_list();
    
    for(i = 0; i < get_n_premios(bd->table_premios); i++){
        galardon = get_premio_i(bd->table_premios, i);
        list_insert(lista, galardon);
    }
    
    return lista;
}

list * find_premiado_by_nombre(data_base *bd, char *nombre){
    list* lista;
    premiado* galardonado;
    int i;
    
    if(!nombre)
        return NULL;
    
    if(!bd)
        return NULL;
        
    lista = new_list();
    
    for(i = 0; i < get_n_premiados(bd->table_premiados); i++){
        galardonado = get_premiado_i(bd->table_premiados, i);
        if(strstr(get_premiado_nombre(galardonado), nombre) != NULL)
            list_insert(lista, galardonado);
    }
    
    return lista;
}

list * find_premio_by_categoria(data_base *bd, char *cat){
    list* lista;
    premio* galardon;
    int i;
    
    if(!bd)
        return NULL;
    
    if(!cat)
        return NULL;
        
    lista = new_list();
    
    for(i = 0; i < get_n_premios(bd->table_premios); i++){
        galardon = get_premio_i(bd->table_premios, i);
        if(strstr(get_premio_categoria(galardon), cat) != NULL)
            list_insert(lista, galardon);
    }
    
    return lista;
}

list *find_apariciones_premiados(data_base *bd){
    list* lista;
    int i, j, contador;
    premio* galardon;
    premiado* galardonado;
    apariciones* apar;
    
    if(!bd)
        return NULL;
        
    lista = new_list();
        
    for(i = 0; i < get_n_premiados(bd->table_premiados); i++){
        contador = 0;
        apar = NULL;
        galardonado = get_premiado_i(bd->table_premiados, i);
        for(j = 0; j < get_n_premios(bd->table_premios); j++){
            galardon = get_premio_i(bd->table_premios, j);
            if(has_premio_premiado(galardon, galardonado) == TRUE){
                if(contador == 0){
                    apar = (apariciones*)malloc(sizeof(apariciones));
                    apar->p = galardonado;
                    apar->n_apariciones = new_premios();
                    add_premio(apar->n_apariciones, galardon);
                    contador++;
                }else{
                    add_premio(apar->n_apariciones, galardon);
                }
            }
        }
        if(apar != NULL)
            list_insert(lista, apar);
    }
    
    return lista;
}

void print_apariciones(apariciones* a){
    if(!a)
        return;
        
    print_premiado(a->p);
    printf("\nNUMERO DE PREMIOS: %d\n", get_n_premios(a->n_apariciones));
}

void destroy_apariciones(apariciones* a){
    if(!a)
        return;
    
    destroy_premios(a->n_apariciones);
    free(a);
}