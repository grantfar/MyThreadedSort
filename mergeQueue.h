#include "entry.h"

typedef struct entryArray{
    int length;
    entry* data;
} entryArray;

typedef struct mergeNode{
    entryArray* Entry;
    struct mergeNode* next;
} mergeNode;

typedef struct mergeQueue{
    mergeNode *head;
    mergeNode *tail;
    int length;
} mergeQueue;



int mCloseQueue(mergeQueue* toClose);
int mInitQueue(mergeQueue* toInit);
entryArray* mDequeue(mergeQueue* theQueue);
int mEnqueue(mergeQueue* theQueue, entryArray* toQueue);