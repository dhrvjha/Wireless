#include "standard_library.h"


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
    freeaddrinfo(res);
    return sockfd;
}