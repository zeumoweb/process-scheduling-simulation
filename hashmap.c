#include "hashmap.h"
#define SIZE 1000000

int hash(int x){
    return x % SIZE;
}

/** Initialize your data structure here. */
HashMap* HashMapCreate() {
    HashMap *obj = malloc(sizeof(HashMap));
    obj->table = malloc(sizeof(int) * SIZE);
    
    int i = 0;
    for (; i < SIZE; i++){
        obj->table[i] = -1;
    }
    
    return obj;
}

/** value will always be non-negative. */
void HashMapPut(HashMap* obj, int key, int value) {
    obj->table[hash(key)] = value;
}

/** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
int HashMapGet(HashMap* obj, int key) {
    return obj->table[hash(key)];
}

/** Removes the mapping of the specified value key if this map contains a mapping for the key */
void HashMapRemove(HashMap* obj, int key) {
    obj->table[hash(key)] = -1;
}

void HashMapFree(HashMap* obj) {
    free(obj);
}

/**
 * Your HashMap struct will be instantiated and called as such:
 * struct HashMap* obj = HashMapCreate();
 * HashMapPut(obj, key, value);
 * int param_2 = HashMapGet(obj, key);
 * HashMapRemove(obj, key);
 * HashMapFree(obj);
 */