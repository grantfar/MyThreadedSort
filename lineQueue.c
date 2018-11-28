#include "lineQueue.h"
#include <stdlib.h>
int initQueue(queue* toInit){
    toInit->head = NULL;
    toInit->tail = NULL;
    toInit->length = 0;
    return 0;
}

int closeQueue(queue* toClose){
    node* next;
    node* current= toClose->head;
    while(current!=NULL){
        free(current->line);
        next = current->next;
        free(current);
        current = next;
    }
    free(toClose);
    return 0;
}

char* dequeue(queue* theQueue){
    if(theQueue->length == 0){
        return NULL;
    }
    char* ret = theQueue->head->line;
    node * toFree = theQueue->head;
    theQueue->head = theQueue->head->next;
    theQueue->length--;
    free(toFree);
    toFree = NULL;
    if(theQueue->head == NULL){
        theQueue->tail = NULL;
    }
    return ret;
}

int enqueue(queue* theQueue, char* toQueue){
    node* n = malloc(sizeof(node));
    n->next = NULL;
    n->line = toQueue;
    if(theQueue->length == 0){
        theQueue->head = n;
        theQueue->tail = n;
    }
    else{
        theQueue->tail->next = n;
        theQueue->tail = n;
    }
    theQueue->length++;
    return 0;
}