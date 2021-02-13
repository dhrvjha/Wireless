//standard library
#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdarg.h>
#include <signal.h>
#include <syscall.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>

#define LOGFILE "/tmp/HTTPserver.log"
#define PORT_A 8080 
#define PORT "8000"
#define PORT_B 8040
#define MAX_BACKLOG 10

#endif //COMMON_H