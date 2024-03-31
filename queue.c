#include "queue.h"


Queue* QueueCreate() {
    Queue* obj = malloc(sizeof(Queue));
    obj->head = 0;
    obj->tail = 0;
    obj->cnt = 0;
    return obj;
}

void QueuePush(Queue* obj, int x) {
    if(obj == NULL) return;
    obj->cnt++;
    obj->ar[obj->tail] = x;
    obj->tail = (obj->tail + 1)%10000;
}

int QueuePop(Queue* obj) {
    if(obj == NULL) return -1;
    
    obj->cnt--;
    int prev_head = obj->head;
    obj->head = (obj->head + 1)%10000;
    return (obj->ar[(prev_head)%10000]);
}

int QueuePeek(Queue* obj) {
    if(obj == NULL) return -1;
    
    return obj->ar[obj->head];
}

int QueueEmpty(Queue* obj) {
    if(obj == NULL) return 0;
    
    return (obj->cnt ? 0 : 1);
}


int QueueSize(Queue* obj) {
    if(obj == NULL) return 0;
    return obj->cnt;
}

void QueueFree(Queue* obj) {
    if(obj == NULL) return;
    free(obj);
}