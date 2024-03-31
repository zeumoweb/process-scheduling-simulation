#include "round_robin_policy.h"

PCB** round_robin_scheduler(char* filename, int quantum) {

    int clock = 0; // Initialize Clock

    HashMap* map = HashMapCreate(); // Maps the process id to the index in the pcb_table
    Queue* ready_queue = QueueCreate(); // Initialize the ready queue

    PCB** pcb_table = process_input_file(filename, map); // Load the tasks into memory
    int num_tasks = getNumLinesInFile(filename); // Get the number of tasks in the file
   
    // while (num_tasks > 0 || QueueEmpty(ready_queue) == 0) {
    int current_task = 0; 
    while (current_task < num_tasks || QueueEmpty(ready_queue) == 0) {

        // While there are tasks to be processed or tasks in the ready queue
        if ((QueueEmpty(ready_queue) == 1) && (current_task < num_tasks)){
            // If the ready queue is empty, add the next task to the ready queue
            QueuePush(ready_queue, pcb_table[current_task]->process_id);
            clock = pcb_table[current_task]->arrival_time;
            current_task ++;

        } 
        while (current_task < num_tasks && pcb_table[current_task]->arrival_time <= clock){
                QueuePush(ready_queue, pcb_table[current_task]->process_id);
                current_task ++;
            }
        

        // Chose the next task to be executed from the ready queue
        int proccess_id = QueuePop(ready_queue);
        int process_index = HashMapGet(map, proccess_id);

        PCB* process = pcb_table[process_index];

        if (process->remaining_time == process->burst_time) {
            process->response_time += clock - process->arrival_time;
        }

        int execution_time = process->remaining_time < quantum ? 
                                process->remaining_time : quantum;

        process->remaining_time -= execution_time;
        clock += execution_time;

        if (process->remaining_time <= 0) {
            process->completion_time = clock;
            process->turnaround_time = process->completion_time - process->arrival_time;
            process->waiting_time =process->completion_time - process->burst_time - process->arrival_time;

    
        } else {
            QueuePush(ready_queue, process->process_id);
        }

        printf("Queue Size: %d\n", QueueSize(ready_queue));
    }
    QueueFree(ready_queue);
    HashMapFree(map);
    return pcb_table;
}