#include <syscall.h>
#include <sys/socket.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h> 

#ifndef PORT
#define PORT 8080
#endif //PORT
#define MAXLNE 4096

void err_n_die(char *message, ...){
    for (int i=0;message[i] != '\0'; i++)
        printf("%c", message[i]);
    printf("\n");
    exit(EXIT_FAILURE);
}

int main(){
    int sockfd, new_socket, valread;
    struct sockaddr_in address;
    char buffer[MAXLNE] = {0};
    char message[MAXLNE] = "Hello";
    int address_size = sizeof(struct sockaddr_in);
    int opt = 1;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        err_n_die("Socket error");
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        err_n_die("setsockopt");
    address.sin_addr.s_addr = inet_addr("192.168.43.182");
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&address, address_size)<0)
        err_n_die("bind failed");
    if (listen(sockfd, 3) < 0)
        err_n_die("Listen error");
    int i=2;
    // if ((new_socket = accept(sockfd, (struct sockaddr *)&address, (socklen_t*)&(address_size))) < 0)
    //     err_n_die("accept error");
    
    while (i--){
        if ((new_socket = accept(sockfd, (struct sockaddr *)&address, (socklen_t*)&(address_size))) < 0)
            err_n_die("accept error");
        valread = read(new_socket, buffer, MAXLNE);
        printf("%s\n",buffer);
        printf("Sending message\n");
        FILE *file = fopen("test.html","r");
        if (file == NULL)
            err_n_die("error opening file");
        while (fgets(message, MAXLNE, file) != NULL)
            send(new_socket, message, strlen(message), 0);
        fclose(file);
    }
    
    
    printf("End of server\n");
    return 0;
}