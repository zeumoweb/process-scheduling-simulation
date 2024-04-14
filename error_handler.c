#include "error_handler.h"

void handle_segfault(int sig) {
    printf("A Segmentation Error Occured %d\n", sig);
    exit(1);
}

void handle_int(int sig) {
    printf("An Error Occured while initializing memory%d\n", sig);
    exit(1);
}

void handle_file_error(int sig) {
    printf("An Error Occured while Opening or Reading the file %d\n", sig);
    exit(1);
}

void handle_heap_full(int sig) {
    printf("Heap is full. Cannot insert new element. Error code: %d\n", sig);
    exit(1);
}