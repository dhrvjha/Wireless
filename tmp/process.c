#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#ifndef _MAX_INPUT
#define _MAX_INPUT 5
#endif // _MAX_INPUT

void parent_process(int *fd){
    wait(NULL);       // wait for child process to finish
    printf("IN PARENT\n");
    close(fd[1]); // close write end of pipe
    int mes[_MAX_INPUT]; // message buffer
    if (read(fd[0], mes, sizeof(mes)/sizeof(int)) == -1){ // read fd[0] to buffer
        printf("Read error in pipe");
        exit(EXIT_FAILURE);
    }
    close(fd[0]);   //close read end of pipe
    printf("From child : ");
    for (int i=0;i<_MAX_INPUT;i++)
        printf("%d ",mes[i]);
    printf("\n");
    return;
}


void child_process(int *fd){
    printf("IN CHILD\n");
    close(fd[0]);   // close read end of pipe
    int mes[_MAX_INPUT]; // input buffer
    printf("message: ");
    for (int i=0;i<_MAX_INPUT;i++)
        scanf("%d",&mes[i]);
    printf("debug |size = %ld\n",sizeof(mes)/sizeof(int));
    if (write(fd[1], mes, sizeof(mes)/sizeof(int)) == -1){ // write to fd[1] with buffer
        printf("Write error in pipe");
        exit(EXIT_FAILURE);
    }
    close(fd[1]);
    return;
}

#ifdef _MAX_INPUT
#undef _MAX_INPUT
#endif //_MAX_INPUT
int main(){
    int fd[2];
    // fd[0] -- read
    // fd[1] -- write
    if (pipe(fd) == -1){
        printf("Error opening pipe\n");
        exit(EXIT_FAILURE);
    }
    pid_t pid = fork();
    if (pid == -1){
        printf("Error creating new process\n");
        exit(EXIT_FAILURE);
    } else if (pid == 0){
        child_process(fd);
    } else {
        parent_process(fd);
    }
    return 0;
}