#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int d;
    double *x;
} vector;

vector *new_vector(int d){
    vector* a;
    
    if(d <= 0)
        return NULL;
    
    a = (vector*)malloc(sizeof(vector));
    
    if(!a)
        return NULL;
    
    a->d = d;
    a->x = (double*)malloc(d * sizeof(double));
    
    return a;
}

void liberar_vector(vector *a){
    if(!a)
        return;
    
    free(a->x);
    free(a);
}

int main(){
    int num, i = 1, j = 0;
    vector* vec;
    
    printf("Introduzca el tamanio del vector: ");
    scanf("%d", &num);
    
    vec = new_vector(num);
    
    while(j < num){
        if(i%2 != 0){
            vec->x[j] = i;
            j++;
        }
        i++;
    }
    
    for(i = 0; i < num; i++){
        printf("%.0f\n", vec->x[i]);
    }
    
    liberar_vector(vec);
    
    return 0;
}