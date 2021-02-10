#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef render_size
#define render_size 25
#endif
void render_dash(char *message){
    int size = strlen(message) - render_size;
    if (size > 0)
        while (size--)
            printf("-");
    else
        printf("----");
}

void check(char *message, int success, int exitcon){
    render_dash(message);
    if (success)    // success == 1
        printf("OK\n");
    else{
        printf("ERROR\n");
        if (exitcon)
            exit(EXIT_FAILURE);
    }
}

void filelog(const char *message, int success){
    FILE *file = fopen("log.txt","a");
    check("Opening log file", file != NULL, 1);
    fprintf(file, "asdfadsf");
    fclose(file);
}