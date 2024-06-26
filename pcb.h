#pragma once
#include "hashmap.h"

// Define the Process Control Block structure
typedef struct PCB {
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int remaining_time;
    int priority;
    int response_time;
    int current_allotment; // Needed for MLFQ
} PCB;

// Function to check if all processes are done
int isAllProcessesDone(PCB **pcb_table, int num_tasks);

// Function to initialize a PCB instance
void initializePCB(PCB *process, int at, int bt);

// Comparison function for qsort
int compare(const void *a, const void *b);

// Bubble sort function
void bubble_sort(PCB **arr, int n, HashMap* map);