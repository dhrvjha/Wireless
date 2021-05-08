#include "standard_library.h"

// this function works after peer is connected to the server
int getipaddress(int sockfd, char *ipstr){
    struct sockaddr_storage their_info;
    socklen_t their_size = sizeof their_info;

    // ERROR :
    // Transport endpoint is not connected
    check("getting peer info", (getpeername(sockfd, (struct sockaddr*)&their_info, &their_size)) >=0, 0);
    struct sockaddr_in *their_addr = (struct sockaddr_in*)&their_info;

    // struct sockaddr_in their_info;
    // socklen_t size_their = sizeof their_info;
    // check("getting peer info", (getpeername(sockfd, (struct sockaddr*)&their_info, &size_their)) >=0, 0);
    inet_ntop(AF_INET, &their_addr->sin_addr, ipstr, sizeof ipstr);

}


void* messageClient(void *sockptr){
    int sockfd = *(int*)sockptr;
    struct sockaddr_storage connector;
    socklen_t addr_size = sizeof connector;
    int new_sockfd;
    check("accpeting",(new_sockfd=accept(sockfd, (struct sockaddr*)&connector, &addr_size))>=0, 1);
    char ip[INET_ADDRSTRLEN];
    getipaddress(sockfd, ip);

    printf("%s connected\n", ip);
    fflush(stdout);
    char request[4096];
    FILE *file = fopen(LOGFILE, "a");
    // char response_str[]  = "<html>HELLO WORLD</html>";
    char *response_str ;
    if (recv(new_sockfd, request, 4090, 0) != 0){
        printf("%s", request);
        fputs(request, file);
        response_str = handler(request);
        fputs(response_str, file);
    }
    size_t response_size = strlen(response_str);
    fclose(file);
    printf("%s\n", response_str);
    send(new_sockfd, response_str, response_size, 0);
    close(new_sockfd);
}