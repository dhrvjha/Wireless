#include "lib/standard_library.h"
#include "lib/make_log.h"
#include <string.h>


/*
    Ready every resourse needed by server to start
    also check every syscall
    return sockfd
*/
int ready_server(struct sockaddr_in server, char *ip){
    int sockfd;
    struct addrinfo hints, *res;
    memset(&hints, '\0',sizeof(hints));
    hints.ai_family = AF_INET;            // use only IPv4
    hints.ai_socktype = SOCK_STREAM;      // use TCP

    check("getting address info", getaddrinfo(ip, PORT, &hints, &res)>=0, 1);
    check("setting socket", (sockfd=socket(res->ai_family, res->ai_socktype, res->ai_protocol))>=0, 1);
    check("binding socket to port", bind(sockfd, res->ai_addr, res->ai_addrlen)>=0, 1);
    check("setting listener", listen(sockfd, MAX_BACKLOG)>=0, 1);

    return sockfd;
}

int messageClient(int sockfd){
    char *mes = "Hello from server\r\n\r\n";
    struct sockaddr_storage connector;
    socklen_t addr_size = sizeof connector;
    int new_sockfd;
    check("accpeting",(new_sockfd=accept(sockfd, (struct sockaddr*)&connector, &addr_size))>=0, 1);
    char brow[4096];
    if(recv(new_sockfd, brow, 4090, 0) == 0)
        printf("Connection closed\n");
    send(new_sockfd, mes, strlen(mes), 0);
    close(new_sockfd);
}

int main(int argc, char **argv){
    filelog("Starting server", 1);

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

    while (1){
        messageClient(sockfd);
    }
    printf("Press any key to exit....\n");
    getchar();

    return 0;
}