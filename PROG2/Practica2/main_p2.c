#include "premiados.h"
#include "premios.h"
#include "data_base.h"
#include "list.h"

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
    int i, id;
    premio* galardon;
    premiado* galardonado;
    list_node* aux;
    char categoria[TAM], nombre[TAM];
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
        printf("*\t1. Twittear                              *\n");
        printf("*\t2. Cuentas                               *\n");
        printf("*\t\t2.1 Iniciar sesion               *\n");
        printf("*\t\t2.2 Registrarse                  *\n");
        printf("*\t3. Consultas                             *\n");
        printf("*\t\t3.1 Todos los premios            *\n");
        printf("*\t\t3.2 Todos los premiados          *\n");
        printf("*\t\t3.3 Buscar premio por ID         *\n");
        printf("*\t\t3.4 Buscar premiado por ID       *\n");
        printf("*\t\t3.5 Buscar premio por categoria  *\n");
        printf("*\t\t3.6 Buscar premiado por nombre   *\n");
        printf("*\t\t3.7 Buscar apariciones premiado  *\n");
        printf("*\t4. Salir                                 *\n");
        printf("**************************************************\n");
        printf("Elige una opcion > ");
        setbuf(stdin,NULL);
        scanf("%lf",&opcion);
        
        if(opcion == 1){
            printf("\nOpcion sin implementar\n");
        }else if(opcion == 2.1){
            printf("\nOpcion sin implementar\n");
        }else if(opcion == 2.2){
            printf("\nOpcion sin implementar\n");
        }else if(opcion == 3.1){
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
        else if(opcion == 3.2){
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
        }else if(opcion == 3.3){
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
        }else if(opcion == 3.4){
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
        }else if(opcion == 3.5){
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
        }else if(opcion == 3.6){
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
        }else if(opcion == 3.7){
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
        else if(opcion != 4){
            printf("\nOPCION INCORRECTA\n");
        }
    }while(opcion != 4);
    
    destroy_data_base(db);
    printf("\nFIN DEL PROGRAMA\n");
    
    return 0;
}