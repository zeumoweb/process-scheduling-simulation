#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "pcb.h"

typedef struct MinHeap {
    PCB *arr;
    int capacity;
    int size;
} MinHeap;

struct MinHeap* createMinHeap(int capacity);

void swap(PCB *a, PCB *b);

void heapifyUp(struct MinHeap* heap, int index);

void heapifyDown(struct MinHeap* heap, int index);

void HeapInsert(struct MinHeap* heap, PCB value);