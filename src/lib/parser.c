
#include "standard_library.h"
#include "parser.h"

/* This will return equivalent int assigned to 
    each method in enum HTTPMethod
*/
int method_select(char *method){
    if (strcmp(method, "GET")) 
        return GET;
}


/* This method parses requestline */
float method_parser(char* requestline, REQUEST *rq){

    // printf("requestline -> %s\n", requestline);
    rq->method = method_select(strtok(requestline, " "));
    // printf("method -> %d\n", rq->method);
    rq->URI = strtok(NULL, " ");
    // printf("URI -> %s\n", rq->URI);
    return (float)atof(strtok(NULL, "/"));
}

/* this will allocate space for REQUEST variables*/
REQUEST init_requests(){
    REQUEST rq;

    rq.misc = malloc(sizeof(char)*256);
    rq.host = malloc(sizeof(char)*256);
}


/*
THis will parse requests from browser
and return a struct REQUEST.
*/
REQUEST HTTPrequest_parser(char *request){
    REQUEST rq = init_requests();
    int size = strlen(request)-1;
    for (int i=0;i<size; i++)
        if (request[i] == '\n' && request[i+1] == '\n')
            request[i+1] == '|';
    char *requestline = strtok(request, "\n");
    // printf("requestline -> %s\n", requestline);
    char *headers = strtok(NULL, "|");
    // printf("headers -> %s\n", headers);
    rq.misc = strtok(NULL, "|");
    // printf("misc -> %s\n", rq.misc);

    rq.HTTPVersion = method_parser(requestline, &rq);

    // printf("method -> %d\n", rq.method);    

    // printf("method -> %s\n", rq.method);
    // body_parser(rq);
    return rq;
}
