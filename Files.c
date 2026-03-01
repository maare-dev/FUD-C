#include <stdio.h>
#include <stdlib.h>
#include <string.h>
FILE* SaveOpenFile(
    FILE *ptr,
    const char *name, 
    const char *mode
){
    ptr = fopen(name, mode);
    if (ptr == NULL){
        fprintf(stderr, "ERR: cannot open file: %s\n", name);
        exit(1);
    }
    return ptr;
}

char* readWord(FILE *ptr){
    char result[256];
    char *word = malloc(256 * sizeof(char));
    if (word == NULL){
        fprintf(stderr, "ERR: cannot allocate memory for word\n");
        exit(1);
    }
    if (fscanf(ptr, "%255s", result) == 1){
        strcpy(word, result);
        return word;
    }
    else{
        free(word);
        return NULL;
    }
}
