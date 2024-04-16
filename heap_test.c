#include "heap.h"
#include <stdio.h>

// Function to print heap content
void printHeap(Heap *heap) {
    printf("Heap contains %d elements: ", heap->size);
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->data[i]->remaining_time);
    }
    printf("\n");
}

// Function to verify min-heap property recursively
int verifyMinHeapProperty(Heap *heap, int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < heap->size && heap->data[left]->remaining_time < heap->data[index]->remaining_time)
        smallest = left;
    if (right < heap->size && heap->data[right]->remaining_time < heap->data[smallest]->remaining_time)
        smallest = right;

    if (smallest != index)
        return 0; // Heap property violated

    return 1; // Heap property maintained
}

// Main function to test heap operations
int main() {
    Heap *heap = HeapCreate(10);
    PCB pcb1 = {1, 0, 10, 0, 0, 0, 0, 10}; // process_id, arrival_time, burst_time, priority...
    PCB pcb2 = {2, 0, 5, 0, 0, 0, 0, 5};
    PCB pcb3 = {3, 0, 3, 0, 0, 0, 0, 3};

    HeapInsert(heap, &pcb1);
    HeapInsert(heap, &pcb2);
    HeapInsert(heap, &pcb3);

    printHeap(heap); // Print heap content to visualize

    // Check heap property
    if (verifyMinHeapProperty(heap, 0)) {
        printf("Heap property is maintained.\n");
    } else {
        printf("Heap property violation.\n");
    }

    PCB *min = HeapGetMin(heap);
    printf("The minimum element is %d\n", min->remaining_time);

    HeapRemoveMin(heap);
    printHeap(heap); // Print after removing min

    HeapFree(heap);
    return 0;
}

