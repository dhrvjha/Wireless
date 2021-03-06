#include "lib/standard_library.h"
#include "lib/readyserver.h"
#include "lib/accept.h"


// int messageClient(int sockfd, FILE *page){
//     char *mes = "Hello from server\r\n\r\n";
//     struct sockaddr_storage connector;
//     socklen_t addr_size = sizeof connector;
//     int new_sockfd;
//     check("accpeting",(new_sockfd=accept(sockfd, (struct sockaddr*)&connector, &addr_size))>=0, 1);
//     char brow[4096];

//     FILE *file = fopen(LOGFILE, "a");
//     if (recv(new_sockfd, brow, 4090, 0) != 0){
//         printf("# %s", brow);
//         fputs(brow, file);
//     }
//     fclose(file);
//     send(new_sockfd, mes, strlen(mes), 0);
//     close(new_sockfd);
// }

void getworkspace_file_name(){
    char filename[30];
    memset(filename, '\0', sizeof(filename));
    for (int i=0; current_path[i] !='\0';i++){
        
    }
}

int main(int argc, char **argv){
    printf("PID: %d\n", getpid());
    filelog("Starting server", 1);
    
    getcwd(current_path, sizeof(current_path));

    struct sockaddr_in addr;
    int sockfd;
    int server_size = sizeof(addr);
    char message[] = "Hello World\r\n\r\n";
    char *ip = (char*)malloc(INET_ADDRSTRLEN*sizeof(char));
    if (argc == 1)
        scanf("%s", ip);
    else
        ip = argv[1];

    sockfd = ready_server(addr, ip);
    printf("Visit : http://%s:%s\n", ip, PORT);
    fflush(stdout);
    while (1){
        messageClient(&sockfd);
    }
    printf("Press any key to exit....\n");
    getchar();

    return 0;
}