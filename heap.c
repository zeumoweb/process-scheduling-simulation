#include "heap.h"

struct MinHeap* createMinHeap(int capacity) {
    struct MinHeap* heap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    heap->capacity = capacity;
    heap->size = 0;
    heap->arr = (PCB*)malloc(sizeof(PCB) * capacity);
    return heap;
}

void swap(PCB *a, PCB *b) {
    PCB temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(struct MinHeap* heap, int index) {
    while (index > 0) {
        int parentIndex = (index - 1) / 2;
        if (heap->arr[index].remaining_time < heap->arr[parentIndex].remaining_time) {
            swap(&heap->arr[index], &heap->arr[parentIndex]);
            index = parentIndex;
        } else {
            break;
        }
    }
}

void heapifyDown(struct MinHeap* heap, int index) {
    int smallest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < heap->size && heap->arr[leftChild].remaining_time < heap->arr[smallest].remaining_time) {
        smallest = leftChild;
    }
    if (rightChild < heap->size && heap->arr[rightChild].remaining_time < heap->arr[smallest].remaining_time) {
        smallest = rightChild;
    }

    if (smallest != index) {
        swap(&heap->arr[index], &heap->arr[smallest]);
        heapifyDown(heap, smallest);
    }
}

void HeapInsert(struct MinHeap* heap, PCB pcb) {
    if (heap->size == heap->capacity) {
        printf("Heap is full\n");
        return;
    }

    heap->arr[heap->size] = pcb;
    heap->size++;
    heapifyUp(heap, heap->size - 1);
}
// int main () {
//     struct MinHeap* heap = createMinHeap(10);
//     PCB pcb1 = {1, 0, 10, 10, 10, 10, 100, 10, 10, 10};
//     PCB pcb2 = {2, 0, 20, 20, 20, 20, 20, 20, 20, 20};
//     PCB pcb3 = {3, 0, 30, 30, 30, 30, 10, 30, 30, 30};
//     PCB pcb4 = {4, 0, 40, 40, 40, 40, 40, 40, 40, 40};
//     PCB pcb5 = {5, 0, 50, 50, 50, 50, 50, 50, 50, 50};
//     insert(heap,pcb1);
//     insert(heap, pcb2);
//     insert(heap, pcb3);
//     insert(heap, pcb4);
//     insert(heap, pcb5);

//     int size = heap->size;
//     for (int i = 0; i < size; i++) {
//         printf("%d ", heap->arr[0].process_id);
//         heap->arr[0] = heap->arr[heap->size - 1];
//         heap->size--;
//         heapifyDown(heap, 0);

//     }
//     printf("\n");
//     return 0;
// }
