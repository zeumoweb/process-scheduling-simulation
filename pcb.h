#pragma once

// Define the Process Control Block structure
typedef struct PCB {
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int priority;
} PCB;

// Function to initialize a PCB instance
void initializePCB(PCB *process, int pid, int at, int bt, int priority);