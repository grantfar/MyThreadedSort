typedef struct node{
    char* line;
    struct node* next;
} node;
typedef struct queue{
    node *head;
    node *tail;
    int length;
} queue;

int enqueue(queue* theQueue, char* toQueue);
char* dequeue(queue* theQueue);
int closeQueue(queue* toClose);
int initQueue(queue* toInit);