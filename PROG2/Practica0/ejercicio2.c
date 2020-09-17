#include <stdio.h>
#include <stdlib.h>

int mostrar_menu()
{
    int opcion;
    
    printf("\nElija una opcion:\n\t0.-Salir del programa\n\t1.-Imprimir numeros pares\n\t2.-Imprimir numeros impares\nOpcion: ");
    scanf("%d",&opcion);
    
    return opcion;
}

void imprimir_pares(int limite)
{
    /* Tu codigo */
    int i;
    
    for(i = 1; i <= limite ; i++){
        if( i%2 == 0)
            printf("%d\n",i);
    }
}

void imprimir_impares(int limite)
{
    /* Tu codigo */
    int i;
    
    for(i = 1; i <= limite ; i++){
        if( i%2 != 0)
            printf("%d\n",i);
    }
}

int main(int argc, char *argv[])
{
    int opcion;
    int limite;
    
    opcion = mostrar_menu();
    
    while(opcion != 0) {
        /* Tu codigo */
        /* Comprobar la opcion e invocar a imprimir_pares o imprimir_impares */
        if(opcion == 1){
            printf("Introduzca el numero limite: ");
            scanf("%d",&limite);
            imprimir_pares(limite);
        }
        else if(opcion == 2){
            printf("Introduzca el numero limite: ");
            scanf("%d",&limite);
            imprimir_impares(limite);
        }
        else{
            printf("\nOpcion incorrecta\n");
        }
        
        opcion = mostrar_menu();
    }
    
    return 0;
}