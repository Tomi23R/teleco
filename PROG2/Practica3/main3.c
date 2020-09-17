#include "premiados.h"
#include "premios.h"
#include "data_base.h"
#include "list.h"
#include "btree.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <strings.h>

#define TAM 100

int main(int argc, char** argv){
    double opcion, tiempo;
    data_base* db;
    list* lista;
    int i, id, anio;
    premio* galardon;
    premiado* galardonado;
    list_node* aux;
    char categoria[TAM], nombre[TAM], pais[TAM], opcion_aux[TAM];
    apariciones* aparic;
    struct timeval ti, tf;
    
    if(argc < 2){
        printf("\nERROR EN EL NUMERO DE ARGUMENTOS\n");
        return -1;
    }
    
    db = new_data_base(argv[1]);
    
    if(db == NULL){
        printf("\nERROR EN EL DIRECTORIO DE LOS FICHEROS\n");
        return -1;
    }
    
    do{
        printf("\n**************************************************\n");
        printf("*\t1. Insertar datos                        *\n");
        printf("*\t\t1.1 Insertar premiado            *\n");
        printf("*\t\t1.2 Insertar premio              *\n");
        printf("*\t2. Consultas                             *\n");
        printf("*\t\t2.1 Todos los premios            *\n");
        printf("*\t\t2.2 Todos los premiados          *\n");
        printf("*\t\t2.3 Buscar premio por ID         *\n");
        printf("*\t\t2.4 Buscar premiado por ID       *\n");
        printf("*\t\t2.5 Buscar premio por categoria  *\n");
        printf("*\t\t2.6 Buscar premiado por nombre   *\n");
        printf("*\t\t2.7 Buscar apariciones premiado  *\n");
        printf("*\t3. Crear indices                         *\n");
        printf("*\t4. Salir                                 *\n");
        printf("**************************************************\n");
        printf("Elige una opcion > ");
        setbuf(stdin,NULL);
        scanf("%lf",&opcion);
        
        if(opcion == 1.1){
            galardonado = new_premiado();
            printf("\nIntroduce el nombre del premiado: ");
            setbuf(stdin, NULL);
            scanf("%s", nombre);
            set_premiado_nombre(galardonado, nombre);
            printf("\nIntroduce la id del premiado: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            set_premiado_id(galardonado, id);
            printf("\nIntroduce el pais del premiado: ");
            setbuf(stdin, NULL);
            scanf("%s", pais);
            set_premiado_pais(galardonado, pais);
            printf("\nIntroduce el genero del premiado: ");
            setbuf(stdin, NULL);
            scanf("%s", categoria);
            if(strcmp(categoria, "hombre") == 0){
                set_premiado_genero(galardonado, HOMBRE);
            }else if(strcmp(categoria, "mujer") == 0){
                set_premiado_genero(galardonado, MUJER);
            }else if(strcmp(categoria, "organismo")){
                set_premiado_genero(galardonado, ORGANISMO);
            }else{
                set_premiado_genero(galardonado, NO_DEFINIDO);
            }
            data_base_add_premiado(db, galardonado);
        }else if(opcion == 1.2){
            galardon = new_premio();
            printf("\nIntroduce la id del premio: ");
            setbuf(stdin, NULL);
            scanf("%d", &id);
            set_premio_id(galardon, id);
            printf("\nIntroduce la categoria del premio: ");
            setbuf(stdin, NULL);
            scanf("%s", categoria);
            set_premio_categoria(galardon, categoria);
            printf("\nIntroduce el anio del premio: ");
            setbuf(stdin, NULL);
            scanf("%d", &anio);
            set_premio_anio(galardon, anio);
            do{
                printf("\nIntroduce la id del premiado que ha ganado este premio o salir para dejar de introducir ids: ");
                setbuf(stdin, NULL);
                scanf("%s", opcion_aux);
                if(strcmp(opcion_aux, "salir") != 0){
                    id = atoi(opcion_aux);
                    galardonado = find_premiado_by_id(db, id);
                    if(galardonado != NULL){
                        add_premio_premiado(galardon, galardonado);
                    }
                    else{
                        printf("\nNo existe ningun premiado con esa id");
                    }
                }
            }while(strcmp(opcion_aux, "salir") != 0);
            data_base_add_premio(db, galardon);
        }else if(opcion == 2.1){
            gettimeofday(&ti, NULL);
            lista = find_all_premios(db);
            gettimeofday(&tf, NULL);
            tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
            printf("\nSe han tardado %lf milisegundos en realizar la consulta\n",tiempo);
            aux = list_first(lista);
            for(i = 0; i < list_size(lista); i++){
                galardon = list_get_data(aux);
                print_premio(galardon);
                aux = list_node_next(aux);
            }
            destroy_list(lista);
        }
        else if(opcion == 2.2){
            gettimeofday(&ti, NULL);
            lista = find_all_premiados(db);
            gettimeofday(&tf, NULL);
            tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
            printf("\nSe han tardado %lf milisegundos en realizar la consulta\n",tiempo);
            aux = list_first(lista);
            for(i = 0; i < list_size(lista); i++){
                galardonado = list_get_data(aux);
                print_premiado(galardonado);
                aux = list_node_next(aux);
            }
            destroy_list(lista);
        }else if(opcion == 2.3){
            printf("Introduce el ID del premio que buscas > ");
            setbuf(stdin,NULL);
            scanf("%d", &id);
            gettimeofday(&ti, NULL);
            galardon = find_premio_by_id(db, id);
            gettimeofday(&tf, NULL);
            tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
            printf("\nSe han tardado %lf milisegundos en realizar la consulta\n",tiempo);
            if(galardon != NULL){
                print_premio(galardon);
            }else{
                printf("\nNo existe ningun premio con ese ID");
            }
        }else if(opcion == 2.4){
            printf("Introduce el ID del premiado que buscas > ");
            setbuf(stdin,NULL);
            scanf("%d", &id);
            gettimeofday(&ti, NULL);
            galardonado = find_premiado_by_id(db, id);
            gettimeofday(&tf, NULL);
            tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
            printf("\nSe han tardado %lf milisegundos en realizar la consulta\n",tiempo);
            if(galardonado != NULL){
                print_premiado(galardonado);
            }else{
                printf("\nNo existe ningun premiado con esa ID");
            }
        }else if(opcion == 2.5){
            printf("\nIntroduce la categoria de premio que buscas > ");
            bzero(categoria, TAM);
            scanf("%s",categoria);
            gettimeofday(&ti, NULL);
            lista = find_premio_by_categoria(db, categoria);
            gettimeofday(&tf, NULL);
            tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
            printf("\nSe han tardado %lf milisegundos en realizar la consulta\n",tiempo);
            if(list_size(lista) < 1){
                printf("\nNo existe ningun premio con esa categoria\n");
            }
            aux = list_first(lista);
            for(i = 0; i < list_size(lista); i++){
                galardon = list_get_data(aux);
                print_premio(galardon);
                aux = list_node_next(aux);
            }
            destroy_list(lista);
        }else if(opcion == 2.6){
            printf("\nIntroduce el nombre del premiado que buscas > ");
            bzero(nombre, TAM);
            scanf("%s",nombre);
            gettimeofday(&ti, NULL);
            lista = find_premiado_by_nombre(db, nombre);
            gettimeofday(&tf, NULL);
            tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
            printf("\nSe han tardado %lf milisegundos en realizar la consulta\n",tiempo);
            if(list_size(lista) < 1){
                printf("\nNo existe ningun premiado con ese nombre\n");
            }
            aux = list_first(lista);
            for(i = 0; i < list_size(lista); i++){
                galardonado = list_get_data(aux);
                print_premiado(galardonado);
                aux = list_node_next(aux);
            }
            destroy_list(lista);
        }else if(opcion == 2.7){
            gettimeofday(&ti, NULL);
            lista = find_apariciones_premiados(db);
            gettimeofday(&tf, NULL);
            tiempo = (tf.tv_sec - ti.tv_sec)*1000 + (tf.tv_usec - ti.tv_usec)/1000.0;
            printf("\nSe han tardado %lf milisegundos en realizar la consulta\n",tiempo);
            aux = list_first(lista);
            for(i = 0; i < list_size(lista); i++){
                aparic = list_get_data(aux);
                print_apariciones(aparic);
                aux = list_node_next(aux);
                destroy_apariciones(aparic);
            }
            destroy_list(lista);
        }
        else if(opcion == 3){
            if(data_base_has_index(db) == TRUE){
                printf("\nLos indices ya estan creados");
            }
            else{
                data_base_make_index(db);
                if(data_base_has_index(db) == TRUE){
                    printf("\nIndices creados correctamente");
                }
                else{
                    printf("\nSe ha producido un error creando los indices");
                }
            }
        }
        else if(opcion != 4){
            printf("\nOPCION INCORRECTA\n");
        }
    }while(opcion != 4);
    
    destroy_data_base(db);
    printf("\nFIN DEL PROGRAMA\n");
    
    return 0;
}