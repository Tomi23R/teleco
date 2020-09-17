#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_W 10

int main(int argc, char** argv){
    char* str = NULL;

    if(argc < 2) return -1;
    str = (char*) realloc(str, MAX_W * sizeof(char) + 1);

    strcpy(str,argv[1]); 

    printf("%s\n",str);
    free(str);
    return 0;
}