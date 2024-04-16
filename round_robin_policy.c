#include "round_robin_policy.h"

pid_t main_process_id_rr;
int global_clock_rr = 0; // clock

  

PCB** round_robin_scheduler(char* filename, int quantum) {

    main_process_id_rr = getpid();

    HashMap* map = HashMapCreate(); // Maps the process id to the index in the pcb_table
    Queue* ready_queue = QueueCreate(); // Initialize the ready queue

    PCB** pcb_table = process_input_file(filename); // Load the tasks into memory
    int num_tasks = getNumLinesInFile(filename); // Get the number of tasks in the file
    bubble_sort(pcb_table, num_tasks, map); // Sort the tasks based on arrival time and process ID


    int current_task = 0; 
    while (current_task < num_tasks || QueueEmpty(ready_queue) == 0) {

        while (current_task < num_tasks && pcb_table[current_task]->arrival_time <= global_clock_rr){
            // Create a new process for the incoming task and add to ready queue
            pid_t pid = fork();
            if (pid == 0 ){
                // child process
                kill(getpid(), SIGUSR1);
            }
            else {

            pcb_table[current_task]->process_id = pid;
            QueuePush(ready_queue, pcb_table[current_task]->process_id);
            HashMapPut(map, pcb_table[current_task]->process_id, current_task); // Maps the process id to the index in the pcb_table
            current_task ++;
            }
        }
        if (getpid() == main_process_id_rr) {

        
        if (QueueEmpty(ready_queue) == 1) {
            global_clock_rr ++;
            continue;
        }
        

        // Chose the next task to be executed from the ready queue
        int proccess_id = QueuePop(ready_queue);
        int process_index = HashMapGet(map, proccess_id);

        PCB* process = pcb_table[process_index];

        if (process->remaining_time == process->burst_time) {
            process->response_time += global_clock_rr - process->arrival_time;
        }

        int execution_time = process->remaining_time < quantum ? 
                                process->remaining_time : quantum;

        process->remaining_time -= execution_time;
        global_clock_rr += execution_time;
        kill(process->process_id, SIGUSR1);

        if (process->remaining_time <= 0) {
            // Process has completed execution
            process->completion_time = global_clock_rr;
            process->turnaround_time = process->completion_time - process->arrival_time;
            process->waiting_time =process->completion_time - process->burst_time - process->arrival_time;
            kill(process->process_id, SIGUSR2);

    
        } else {
            QueuePush(ready_queue, process->process_id);
        }
    }}
    QueueFree(ready_queue);
    HashMapFree(map);
    return pcb_table;
}