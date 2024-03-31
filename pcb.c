#include "pcb.h"

// Function to initialize a PCB instance
void initializePCB(PCB *process, int pid, int at, int bt, int priority) {
    process->process_id = pid;
    process->arrival_time = at;
    process->burst_time = bt;
    process->priority = priority;
    process->completion_time = 0;
    process->turnaround_time = 0;
    process->waiting_time = 0;
    process->remaining_time = bt;
    process->response_time = 0;
    process->current_allotment = 0;
}


int compare(const void *a, const void *b) {
    const PCB *pcb1 = (const PCB *)a;
    const PCB *pcb2 = (const PCB *)b;

    // If arrival time is different, sort based on arrival time
    if (pcb1->arrival_time != pcb2->arrival_time) {
        return pcb1->arrival_time - pcb2->arrival_time;
    }

    // If arrival time is the same, sort based on process_id
    return pcb1->process_id - pcb2->process_id;
}

// Bubble sort function
void bubble_sort(PCB **arr, int n, HashMap* map) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            // Compare PCBs based on arrival time and process ID
            if (compare(arr[j], arr[j + 1]) > 0) {
                // Swap PCBs if they are out of order
                PCB* temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
                HashMapPut(map, arr[j]->process_id, j);
                HashMapPut(map, arr[j + 1]->process_id, j + 1);
            }
        }
    }
}