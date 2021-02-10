#include "standard_library.h" //all standard libraries
#include "make_log.h"         //log(), check()


//setup_server to set server at IP:PORT
/*
*TODO:
* -add threads
* -add select
*
*/
struct sockaddr_in addresssetup(){
    printf("IP address (Wifi/ Ethernet): ");
    char *ip_address = malloc(16*sizeof(char));
    scanf("%s", ip_address);

    //setup address
    struct sockaddr_in serverfd;
    // serverfd.sin_addr.s_addr = inet_addr(ip_address);
    serverfd.sin_addr.s_addr = INADDR_ANY;
    serverfd.sin_family = AF_INET;
    serverfd.sin_port = htons(PORT);
    free(ip_address);
    return serverfd;
}

void setup_server(){
    struct sockaddr_in server = addresssetup();
    struct sockaddr_in client_info;
    int serverfd, opt =1;
    check("initializing socket",(serverfd = socket(AF_INET, SOCK_STREAM, 0)), 1);
    check("setting up socket",  (setsockopt(serverfd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))), 1);
    check("binding to client",  (bind(serverfd, (struct sockaddr *)&client_info, sizeof(client_info)))+1, 1);
    check("listening on socket",(listen(serverfd, 3))+1, 1);
    
    // while(1){
        int new_socket, clientinfo_size = sizeof(client_info);
        check("Accepting",(new_socket = accept(serverfd, (struct sockaddr *)&client_info, (socklen_t*)&(clientinfo_size))+1), 0);
        //TODO:
        // - message code.
    // }
    return;
}

int main(){
    setup_server();
    return 0;
}