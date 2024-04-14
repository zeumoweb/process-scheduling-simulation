#include "heap.h"

Heap* HeapCreate(int capacity) {
    Heap* heap = malloc(sizeof(Heap));
    heap->data = malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

void HeapInsert(Heap* heap, int value) {
    // First, make sure the heap has room for a new element
    if (heap->size == heap->capacity) {  
        // Heap is full
        handle_heap_full(1);
        return;
    }

    // Insert the new value at the end of the heap
    heap->data[heap->size] = value;

    // Move the new value up the heap until it's in the correct position
    int i = heap->size;
    while (i != 0 && heap->data[i] < heap->data[(i - 1) / 2]) {
        // Swap the new value with its parent
        int temp = heap->data[i];
        heap->data[i] = heap->data[(i - 1) / 2];
        heap->data[(i - 1) / 2] = temp;

        // Move to the parent's position
        i = (i - 1) / 2;
    }

    // Increment the size of the heap
    heap->size++;
}

int HeapGetMin(Heap* heap) {
    if (heap->size == 0) {
        // Heap is empty
        return -1;
    }

    // Return the root of the heap
    return heap->data[0];
}

void HeapRemoveMin(Heap* heap) {
    if (heap->size == 0) {
        // Heap is empty
        return;
    }

    // Move the last element in the heap to the root
    heap->data[0] = heap->data[heap->size - 1];

    // Decrement the size of the heap
    heap->size--;

    // Move the new root down the heap until it's in the correct position
    int i = 0;
    while (1) {
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;

        // Find the smallest child
        int smallest = i;
        if (leftChild < heap->size && heap->data[leftChild] < heap->data[smallest]) {
            smallest = leftChild;
        }
        if (rightChild < heap->size && heap->data[rightChild] < heap->data[smallest]) {
            smallest = rightChild;
        }

        // If the smallest child is the parent, the heap property is restored
        if (smallest == i) {
            break;
        }

        // Swap the parent with the smallest child
        int temp = heap->data[i];
        heap->data[i] = heap->data[smallest];
        heap->data[smallest] = temp;

        // Move to the smallest child's position
        i = smallest;
    }
}

void HeapFree(Heap* heap) {
    free(heap->data);  // Deallocates the memory previously allocated by malloc to the data array in the heap
    free(heap);  // Deallocates the memory previously allocated by malloc to the heap itself
}