#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#ifndef render_size
#define render_size 25
#endif


int errstatus;
char *dash;
void render_dash(const char *message){
    int size = strlen(message) - render_size;
    if (size > 0){
        dash = (char*)malloc(size * sizeof(char) + 1);
        for (int i=0;i<size;i++)
            dash[i] = '-';
    }
    else{
        dash = (char*)malloc(5 * sizeof(char) +1);
        dash = "-----";
    }
}

void filelog(const char *message, int success){
    FILE *file = fopen("/tmp/HTTPserver.log", "a");
    render_dash(message);
    if (file == NULL){
        printf("Error Opening log file\n");
        return;
    }
    fputs(message, file);
    fputs(dash, file);
    if (success)
        fputs("OK", file);
    else{
        fputs("ERROR: ", file);
        fputs(strerror(errstatus), file);
    }
    fputs("\n", file);
    fclose(file);
}

void check(char *message, int success, int exitcon){
    errstatus = errno;
    filelog(message, success);
    if (success)
        printf("%s%sOK\n", message, dash);
    else{
        printf("%s%sERROR(%d): %s\n", message, dash,errstatus,strerror(errstatus));
        if (exitcon)
            exit(EXIT_FAILURE);
    }
}
