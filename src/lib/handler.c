#include "standard_library.h"
#include <dirent.h>

// char response_headers[]=
// "Connection: Keep-Alive\nContent-Encoding: gzip\nContent-Type: html; charset=utf-8\nDate: Wed, 07 Mar 2021 10:55:30 GMT\nVary: Cookie, Accept-Encoding\n\n";

char status[10];
char anchor_html[] = "<a href=\"";
char anchor_close_html[] = "\"></a>";
char header_html[] = "<!DOCTYPE html PUBLIC \" - //IETF//DTD HTML 2.0//EN\">\n<html lang=\"en\" dir=\"ltr\">\n<head>\n";
                     char title_html[30];
char body_html[] = "</head>\n<body>\n<h4>\n";
char *folder_html;
char close_h4_html[] = "</h4>\n";
char content_html[4096];
char footer_html[] = "</body>\n</html>\n";


struct dirent* find_file(char *path, char *URI){
    printf("Opening (DIR) --> %s\n", path);
    DIR *dir;
    check("searching for request ",(dir = opendir(path))!=NULL, 1);

    struct dirent* entity;
    entity = readdir(dir);


    while (entity!=NULL){
        if (strcmp(entity->d_name, URI)==0)
            return entity;
        entity = readdir(dir);
    }
    return NULL;
}

int responde_folder(char *path){
    DIR *dir;
    check("opening dir", (dir = opendir(path)) != NULL, 1);

    struct dirent* entity = readdir(dir);
    memset(content_html, '\0', sizeof(content_html));
    while (entity != NULL){
        strcat(content_html, entity->d_name);
        strcat(content_html, "<br>\n");
        entity = readdir(dir);
    }

    return STATUS_OK;
}

int responde_file(char *path_to_file){
    FILE *file = fopen(path_to_file, "r");
    char c;
    int i=0;
    memset(content_html, '\0', sizeof(content_html));
    while ((c = fgetc(file)) != 0){
        content_html[i++] = c;
        if (i > 4094)
            break;
    }

    content_html[i] = '\0';
    fclose(file);
    return STATUS_OK;
}

int search_URI(char *URI){
    printf("\n\nURI %s\n\n", URI);
    char *bf = strtok(URI, "/");
    char path[1024] = {0};
    strcat(path, current_path);
    struct dirent *entity;
    while (bf != NULL){
        entity = find_file(path, bf);
        if (entity == NULL) // if file is not present in folder
            return STATUS_NOT_FOUND;

        strcat(path, "/");
        strcat(path, entity->d_name); // updating path to new path

        bf = strtok(NULL, "/");
    }
    if (entity == NULL) // if file is not present in folder
        return STATUS_NOT_FOUND;

    folder_html = entity->d_name;
    switch(entity->d_type){
    case DT_DIR:
        return responde_folder(path);
        break;
    case DT_REG:
        return responde_file(path);
        break;
    default:
        return 404;
    }
    return STATUS_NOT_FOUND;
}

void getfoldername(char *dest, char *src){
    int lastoccurenceofFslash=0;
    for (int i=0;src[i] !='\0';i++){
        if (src[i] == '/')
            lastoccurenceofFslash = i;
    }
    for (int j=0, i=lastoccurenceofFslash+1; src[i]!='\0';i++, j++){
        dest[j] = src[i];
    }
}


char* handler(char *request){
    char *everything = malloc(sizeof(char)*10000);
    REQUEST rq = HTTPrequest_parser(request);
    int status_code;

    // home path
    if (strcmp(rq.URI, "/") == 0){
        status_code = responde_folder(current_path);
        folder_html = malloc(sizeof(char)*30);
        getfoldername(folder_html, current_path);

    // favicon.ico is icon for favourites icon
    } else if (strcmp(rq.URI, "/favicon.ico")==0){
        // FILE *file;
        // if (check("opening favico", (file=fopen("favicon.ico", "r"))!=NULL, 0)==0)
        //     return "";
        // char buffer;
        // // strcat(everything, "200 OK");
        // // strcat(everything, response_headers);
        // while ((buffer = fgetc(file)) != '\0'){
        //     strcat(everything, &buffer);
        // }
        // strcat(everything, "\r\n\r\n");

        // return everything;
        return "";
    }
    else
        status_code = search_URI(rq.URI);
    sprintf(status, "%d", status_code);
    switch (status_code)
    {
    case STATUS_OK:
        strcat(status, " OK\n");
        break;
    case STATUS_NOT_FOUND:
        strcat(status, " NOT FOUND\n");
        break;
    default:
        break;
    }
    int co=0;
    strcat(everything, status);
    // strcat(everything, response_headers);
    strcat(everything, header_html);
    strcat(everything, title_html);
    strcat(everything, body_html);
    strcat(everything, folder_html);
    strcat(everything, close_h4_html);
    strcat(everything, content_html);
    strcat(everything, footer_html);
    strcat(everything, "\r\n\r\n");
    return everything;
}

void printrequest(char *request){
    REQUEST rq = HTTPrequest_parser(request);
    printf("%d\n%s\n",rq.method, rq.URI);

    printf("%s\n", rq.URI);

}

// int main(){
//     char ac[] = "GET /favicon.ico HTTP/1.1\nUser-Agent: Mozilla/5.0 (Android 10; Mobile; rv:68.4.2) Gecko/68.4.2 Firefox/68.4.2\nHost: 192.168.29.242:8080\nConnection: Keep-Alive\nAccept-Encoding: gzip\n\nq=0.8\nAccept-Language: en-US,en;q=0.5\nAccept-Encoding: gzip, deflate\nDNT: 1\nConnection: keep-alive\nUpgrade-Insecure-Requests: 1\n";
//     printrequest(ac);
//     return 0;
// }
