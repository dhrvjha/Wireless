#include "standard_library.h"


typedef struct Node{
    int val;
    struct node *next;
}Node;

Node* top = NULL;
Node* last = NULL;

int DEQUEUE(){
    if (top == NULL){
        errno = EACCES;
        return -1;
    }
    if (top == last){
        int val = top->val;
        free(top);
        top = last = NULL;
        return val;
    } else {
        Node* tmp = (struct Node*)top->next;
        int val = top->val;
        free(top);
        top = tmp;
        return val;
    }
    return -2;
}

int ENQUEUE(void *args){
    if (top == NULL){
        top = (Node*)malloc(sizeof(Node));
        if (top == NULL){
            return -1;//failure
        }
        top->val = *(int*)args;
        last = top;
        return 1;
    }
    else{
        Node* tmp = (Node*)malloc(sizeof(Node));
        if (tmp == NULL)
            return -1;
        tmp->val = *(int*)args;
        last->next = tmp;
        last = last->next;
        return 2;
    }
    return -2;
}
