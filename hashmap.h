#pragma once
#include <stdlib.h>

typedef struct {
    int *table;
} HashMap;

int hash(int x);
HashMap* HashMapCreate();
void HashMapPut(HashMap* obj, int key, int value);
int HashMapGet(HashMap* obj, int key);
void HashMapRemove(HashMap* obj, int key) ;
void HashMapFree(HashMap* obj);