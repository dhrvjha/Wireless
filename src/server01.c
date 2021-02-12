#include "lib/standard_library.h"

int main(int argc, char **argv){
    struct addrinfo hints, *res, *p;
    int status;
    char ipstr[INET6_ADDRSTRLEN];

    if (argc < 2){
        fprintf(stderr, "add argumet\n");
        exit(EXIT_FAILURE);
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0){
        fprintf(stderr,"getaddrinfo error\n");
        return 2;
    }

    printf("IP address for %s\n", argv[1]);

    for (p=res; p!=NULL;p = p->ai_next){
        void *addr;
        char *ipver;

        if (p->ai_family == AF_INET){
            struct sockaddr_in *tmp = (struct sockaddr_in*)p->ai_addr;
            addr = &(tmp->sin_addr);
            ipver = "IPv4";
        } else if (p->ai_family == AF_INET6){
            struct sockaddr_in6 *tmp = (struct sockaddr_in6*)p->ai_addr;
            addr = &(tmp->sin6_addr);
            ipver = "IPv6";
        }
        
        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf(" %s: %s: %d\n", ipstr, ipver, p->ai_socktype);
    }
    freeaddrinfo(res);
    return 0;
}
