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
}
