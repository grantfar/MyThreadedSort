#include "mergeQueue.h"
#include <stdlib.h>
int mInitQueue(mergeQueue* toInit){
    toInit->head = NULL;
    toInit->tail = NULL;
    toInit->length = 0;
    return 0;
}

int mCloseQueue(mergeQueue* toClose){
    mergeNode* next;
    mergeNode* current= toClose->head;
    while(current!=NULL){
        free(current->Entry);
        next = current->next;
        free(current);
        current = next;
    }
    free(toClose);
    return 0;
}

entryArray* mDequeue(mergeQueue* theQueue){
    if(theQueue->length == 0){
        return NULL;
    }
    entryArray* ret = theQueue->head->Entry;
    mergeNode * toFree = theQueue->head;
    theQueue->head = theQueue->head->next;
    theQueue->length--;
    free(toFree);
    toFree = NULL;
    if(theQueue->head == NULL){
        theQueue->tail = NULL;
    }
    return ret;
}

int mEnqueue(mergeQueue* theQueue, entryArray* toQueue){
    mergeNode* n = malloc(sizeof(mergeNode));
    n->next = NULL;
    n->Entry = toQueue;
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