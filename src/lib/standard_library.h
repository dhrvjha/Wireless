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
#include <errno.h>

#include "make_log.h"
#include "parser.h"
#include "queue.h"
#include "handler.h"

#define LOGFILE "/tmp/HTTPserver.log"
#define PORT "8080"
#define PORT_A "8000"
#define PORT_B 8040
#define MAX_BACKLOG 100

#define STATUS_NOT_FOUND 404
#define STATUS_OK 200

struct response{
    int sockfd;
    char *request;
};

char current_path[1024];

#endif //COMMON_H