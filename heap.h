#include <stdlib.h>
#include "error_handler.h"

typedef struct {
    int *data;
    int size;
    int capacity;
} Heap;

Heap* HeapCreate(int capacity);
void HeapInsert(Heap* heap, int value);
int HeapGetMin(Heap* heap);
void HeapRemoveMin(Heap* heap);
void HeapFree(Heap* heap);