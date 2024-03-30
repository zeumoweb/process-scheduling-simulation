#pragma once
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int ar[100];
    int head;
    int tail;
    int cnt;
} Queue;

Queue* QueueCreate();

void QueuePush(Queue* obj, int x);

int QueuePop(Queue* obj);

int QueuePeek(Queue* obj);

int QueueEmpty(Queue* obj);

void QueueFree(Queue* obj);