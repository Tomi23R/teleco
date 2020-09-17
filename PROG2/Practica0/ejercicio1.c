#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int num;
    int i;
    
    if ( argc < 2 ) {
        printf("Se esperaba un parámetro.\n");
        return -1;
    }  
    
    num = atoi(argv[1]);

    /* El código de tu programa */
    for( i = 1 ; i <= num ; i++){
        if(i % 3 == 0)
            printf("%d\n",i);
    }
    
    return 0;
}