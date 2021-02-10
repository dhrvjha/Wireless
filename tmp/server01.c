#include <syscall.h>
#include <sys/socket.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <fcntl.h>
#include <netinet/in.h> 
#include <string.h>

#ifndef PORT
#define PORT 8080
#endif //PORT
void err_n_die(char *message, ...){
    for (int i=0;message[i] != '\0'; i++)
        printf("%c", message[i]);
    printf("\n");
    exit(EXIT_FAILURE);
}
struct ip_config{
    char ipaddress[16];
    int port;
};

void setup_server(){
    struct sockaddr_in server;
    char message[] = "Hello from server";
    int sockfd, opt=1;
    // struct ip_config config = input();
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
        err_n_die("Error: socket returned 0");
    else
        printf("Started Socket\n");
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        err_n_die("Error: setting up socket error");
    else
        printf("Setting up socket.........OK\n");
    if (bind(sockfd, (struct sockaddr *)&server, sizeof(server))<0)
        err_n_die("Error: Binding");
    else
        printf("Binding socket............OK\n");
    if (listen(sockfd, 3) < 0)
        err_n_die("Error: Setting up listening");
    else
        printf("Listening at PORT %d\n",PORT);
    int server_size = sizeof(server);
    int new_socket;
    if ((new_socket = accept(sockfd, (struct sockaddr *)&server, (socklen_t*)&(server_size))) < 0)
        err_n_die("Error: accepting");
    else
        err_n_die("Accepting.............OK\n");
    printf("Sending message : %s", message);
    send(new_socket, message,strlen(message), 0);
    printf("Press any key to exit....");
    getchar();
}

// struct ip_config input(){
//     struct ip_config config;
//     printf("IP address: ");
//     scanf("%s", &config.ipaddress);
//     printf("Port: ");
//     scanf("%d",&config.port);
//     return config;
// }

int main(){
    setup_server();
    return 0;
}