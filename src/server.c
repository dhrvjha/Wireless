#include "lib/standard_library.h"
#include "lib/make_log.h"
#include <string.h>


int main(){
    filelog("Starting server", 1);

    struct sockaddr_in addr;
    int sockfd, opt=1;
    int server_size = sizeof(addr);
    int new_socket;
    char message[] = "Hello World";

    char ip[16];
    scanf("%s", ip);
    check("Converting IP to binary", inet_pton(AF_INET, ip, &(addr.sin_addr))>0, 1);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);

    check("Initializing socket",(sockfd = socket(AF_INET, SOCK_STREAM, 0)) >= 0,1);
    check("Setting up socket", setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)) >= 0, 1);
    check("Binding",bind(sockfd, (struct sockaddr *)&addr, sizeof(addr))+1 ,1);
    check("Listening", (listen(sockfd, 3))+1, 1);
    check("Accepting", (new_socket = accept(sockfd, (struct sockaddr *)&addr, (socklen_t*)&(server_size))) >= 0, 1);
    printf("Sending message : %s", message);
    send(new_socket, message,strlen(message), 0);
    printf("Press any key to exit....");
    getchar();

    return 0;
}