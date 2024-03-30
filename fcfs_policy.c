#include "pcb.h"

/*
 Update the PCB of each process with the corresponding waiting time, turn around time, and completion time
 When scheduling the processes/Jobs with first come first serve algorithm.

 process_ids contains the list of process id in the order in which they arrived in the ready queue.
*/
void fcfs_scheduler(PCB *pcb_table, int *process_ids)
{
 int num_processes = sizeof(process_ids)/sizeof(process_ids[0]);
 for (int i = 0; i < num_processes; i++){
    int pid = process_ids[i];
    pcb_table[pid].waiting_time = pcb_table[pid].burst_time;

    // CT = BT + CT of previous process
    pcb_table[pid].completion_time = pcb_table[pid].burst_time + pcb_table[(pid > 0) ? pid - 1 : 0].completion_time;

    // TAT = CT - AT
    pcb_table[pid].turnaround_time = pcb_table[pid].completion_time - pcb_table[pid].arrival_time;

    // WT = TAT - BT
    pcb_table[pid].waiting_time = pcb_table[pid].turnaround_time - pcb_table[pid].burst_time;
 }   

}