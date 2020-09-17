#include "premiados.h"
#include "premios.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOMBRE 100

int main(){
    int id, anio, genero, i;
    char nombre[MAX_NOMBRE], pais[MAX_NOMBRE];
    double opcion;
    premiado* galardonado;
    premio* galardon;
    premios* galardones;
    premiados* galardonados;
    
    galardones = new_premios();
    galardonados = new_premiados();
    
    do{
        printf("\n1. Insertar datos\n");
        printf("\t1.1 Insertar premiado\n");
        printf("\t1.2 Insertar premio\n");
        printf("2. Consultas\n");
        printf("\t2.1 Todos los premiados\n");
        printf("\t2.2 Todos los premios\n");
        printf("\t2.3 Premios que incluyan a un premiado\n");
        printf("3. Salir\n");
        printf("Elige una opcion > ");
        scanf("%lf",&opcion);
        if(opcion == 1.1){
            printf("\nIntroduce los datos del premiado:\n");
            printf("Identificador (numero): ");
            scanf("\n%d",&id);
            printf("\nNombre (100 caracteres): ");
            setbuf(stdin,NULL);
            fgets(nombre, MAX_NOMBRE, stdin);
            printf("\nPais: ");
            fgets(pais, MAX_NOMBRE, stdin);
            genero = 4;
            while(genero < 0 || genero >3 ){
                printf("\nGenero (0-HOMBRE, 1-MUJER, 2-ORGANISMO, 3-NO_DEFINIDO): ");
                scanf("%d",&genero);
            }
            galardonado = new_premiado();
            set_premiado_id(galardonado, id);
            set_premiado_genero(galardonado,genero);
            set_premiado_nombre(galardonado, nombre);
            set_premiado_pais(galardonado, pais);
            add_premiado(galardonados, galardonado);
        }else if(opcion == 1.2){
            printf("\nIntroduce los datos del premio:\n");
            printf("Identificador (numero): ");
            scanf("%d",&id);
            printf("\nCategoria: ");
            setbuf(stdin,NULL);
            fgets(nombre, MAX_NOMBRE, stdin);
            printf("\nAnio: ");
            scanf("%d", &anio);
            galardon = new_premio();
            set_premio_id(galardon, id);
            set_premio_categoria(galardon, nombre);
            set_premio_anio(galardon, anio);
            id = 0;
            while(id != -1){
                printf("\nInserta premiados por codigo (-1 para terminar): ");
                scanf("\n%d", &id);
                galardonado = get_premiado_by_id(galardonados, id);
                if(galardonado != NULL){
                    printf("\nInsertando premiado...\n");
                    add_premio_premiado(galardon, galardonado);
                }
                else if(id != -1){
                    printf("\nNo existe un premiado con ese codigo\n");
                }
            }
            add_premio(galardones, galardon);
        }else if(opcion == 2.1){
            print_premiados(galardonados);
        }else if(opcion == 2.2){
            print_premios(galardones);
        }else if(opcion == 2.3){
            printf("\nIntroduce el id del premiado a buscar: ");
            scanf("%d", &id);
            galardonado = get_premiado_by_id(galardonados, id);
            print_premiado(galardonado);
            if(galardonado != NULL){
                for(i = 0; i < get_n_premios(galardones); i++){
                    galardon = get_premio_i(galardones, i);
                    if(has_premio_premiado(galardon, galardonado) == TRUE){
                        printf("\nPremios obtenidos por el premiado\n\tId: %d\n\tCategoria: %s\tAnio: %d\n", get_premio_id(galardon), get_premio_categoria(galardon), get_premio_anio(galardon));
                    }
                }
            }else
                printf("\nNo existe ningun premiado con esa id\n");
        }else if(opcion != 3)
            printf("\nOpcion incorrecta\n");
    }while(opcion!=3);
    
    for(i = 0; i < get_n_premiados(galardonados); i++){
        galardonado = get_premiado_i(galardonados, i);
        destroy_premiado(galardonado);
    }
    for(i = 0; i < get_n_premios(galardones); i++){
        galardon = get_premio_i(galardones, i);
        destroy_premio(galardon);
    }
    destroy_premiados(galardonados);
    destroy_premios(galardones);
    
    return 0;
}