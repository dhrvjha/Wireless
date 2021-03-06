#include "standard_library.h"
#include <dirent.h>

char anchor_html[] = "<a href=\"";
char anchor_close_html[] = "\"></a>";
char header_html[] = "<!DOCTYPE html><html lang=\"en\" dir=\"ltr\"><head>";
char title_html[30];
char body_html[] = "</head><body><h4>";
char *folder_html;
char close_h4_html[] = "</h4>";
char content_html[4096];
char footer_html[] = "</body></html>";


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
        strcat(content_html, "<br>");
        entity = readdir(dir);
    }

    return STATUS_OK;
}

int responde_file(char *path_to_file){
    FILE *file = fopen(path_to_file, "r");
    char c;
    int i=0;
    memset(content_html, '\0', sizeof(content_html));
    while ((c = fgetc(file)) != 0 || c != NULL){
        content_html[i++] = c;
        if (i > 4094)
            break;
    }
    
    content_html[i] = '\0';
    fclose(file);
    return STATUS_OK;
}

int search_URI(char *URI){
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



char* handler(char *request){
    char *everything = malloc(sizeof(char)*10000);
    REQUEST rq = HTTPrequest_parser(request);
    printf("RequestURI at handler --> %s\n", rq.URI);
    int status_code;
    if (strcmp(rq.URI, "/") == 0)
        status_code = responde_folder(current_path);
    else
        status_code = search_URI(rq.URI);
    printf("Status Code --> %d\n", status_code);
    char status[10];
    sprintf(status, "%d", status_code);
    printf("Status Code as string --> %s\n", status);
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
    strcat(everything, status);
    strcat(everything, header_html);
    strcat(everything, title_html);
    strcat(everything, body_html);
    strcat(everything, folder_html);
    strcat(everything, close_h4_html);
    strcat(everything, content_html);
    strcat(everything, footer_html);


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
