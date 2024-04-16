#ifndef HEAP_H
#define HEAP_H

#include <stdlib.h>
#include "error_handler.h"
#include "pcb.h"


typedef struct {
    PCB **data;    // Array of pointers to PCB structures
    int size;      // Number of elements currently in the heap
    int capacity;  // Total capacity of the heap
} Heap;

// Function to create a new heap with a specified capacity
Heap* HeapCreate(int capacity);

// Function to insert a PCB into the heap
void HeapInsert(Heap* heap, PCB* pcb);

// Function to get the PCB with the minimum value (based on scheduling criteria) from the heap
PCB* HeapGetMin(Heap* heap);

// Function to remove the PCB with the minimum value from the heap
void HeapRemoveMin(Heap* heap);

// Function to free the heap and all associated memory
void HeapFree(Heap* heap);

#endif // HEAP_H
