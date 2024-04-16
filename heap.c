#include "heap.h"
#include <stdbool.h>
#include <string.h>  // For memcpy

Heap* HeapCreate(int capacity) {
    Heap* heap = malloc(sizeof(Heap));
    if (!heap) return NULL; // Always good to check for malloc failure
    heap->data = malloc(capacity * sizeof(PCB*)); // Allocate space for PCB pointers
    if (!heap->data) { // Check for malloc failure
        free(heap);
        return NULL;
    }
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

// Function to get the PCB with the minimum value from the heap
PCB* HeapGetMin(Heap* heap) {
    if (heap->size == 0) {
        return NULL; // Heap is empty, return NULL
    }
    return heap->data[0]; // Return the root element of the heap, which is the minimum
}



void HeapInsert(Heap* heap, PCB* pcb) {
    if (heap->size == heap->capacity) {
        // Need to resize the heap to accommodate more elements
        int newCapacity = heap->capacity * 2;  // Double the capacity
        PCB** newData = malloc(newCapacity * sizeof(PCB*));  // Allocate new, larger array
        if (newData == NULL) {
            // Handle allocation failure; could return an error code or exit
            fprintf(stderr, "Failed to allocate memory for heap resize.\n");
            exit(EXIT_FAILURE);
        }
        memcpy(newData, heap->data, heap->capacity * sizeof(PCB*));  // Copy existing data to new array
        free(heap->data);  // Free the old array
        heap->data = newData;  // Assign the new array to the heap
        heap->capacity = newCapacity;  // Update the capacity
    }

    // Proceed with the standard insertion process
    heap->data[heap->size] = pcb;
    int childIndex = heap->size;
    int parentIndex = (childIndex - 1) / 2;
    while (childIndex > 0 && heap->data[childIndex]->remaining_time < heap->data[parentIndex]->remaining_time) {
        // Swap child and parent
        PCB* temp = heap->data[childIndex];
        heap->data[childIndex] = heap->data[parentIndex];
        heap->data[parentIndex] = temp;
        childIndex = parentIndex;
        parentIndex = (childIndex - 1) / 2;
    }
    
    heap->size++;
}



void HeapRemoveMin(Heap* heap) {
    if (heap->size == 0) {
        return;
    }
    // Move the last element to the root
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;

    // Re-heapify down from the root
    int currentIndex = 0;
    while (true) {
        int smallest = currentIndex;
        int leftChild = 2 * currentIndex + 1;
        int rightChild = 2 * currentIndex + 2;

        if (leftChild < heap->size && heap->data[leftChild]->remaining_time < heap->data[smallest]->remaining_time) {
            smallest = leftChild;
        }
        if (rightChild < heap->size && heap->data[rightChild]->remaining_time < heap->data[smallest]->remaining_time) {
            smallest = rightChild;
        }

        if (smallest == currentIndex) {
            break;
        }

        // Swap the current node with the smallest child
        PCB* temp = heap->data[currentIndex];
        heap->data[currentIndex] = heap->data[smallest];
        heap->data[smallest] = temp;

        currentIndex = smallest; // Move to the smallest child
    }
}


void HeapFree(Heap* heap) {
    if (!heap) return;
    free(heap->data); // Deallocate the array of PCB pointers
    free(heap);       // Deallocate the heap structure itself
}
