#include "sjf_preemptive.h"

pid_t main_process_id;
int global_clock_sjf = 0; // global_clock_

PCB **sjf_preemptive(char *filename)
{
    signal(SIGUSR1, execute_process);
    signal(SIGUSR2, execute_process);
    main_process_id = getpid();

    HashMap *map = HashMapCreate();                      // Maps the process id to the index in the pcb_table
    PCB **pcb_table = process_input_file(filename, map); // Load the tasks into memory
    int num_tasks = getNumLinesInFile(filename);         // Get the number of tasks in the file

    MinHeap *minHeap = createMinHeap(num_tasks); // Initialize the min heap

    bubble_sort(pcb_table, num_tasks, map); // Sort the tasks based on arrival time and process ID

    int current_task = 0;
    while (isAllProcessesDone(pcb_table, num_tasks) == 0)
    {
        // Check all the processes that have arrived and add them to the priority queue
        while (current_task < num_tasks && pcb_table[current_task]->arrival_time <= global_clock_sjf)
        {
            pid_t pid = fork();
            if (pid == 0)
            {
                // child process
                kill(getpid(), SIGUSR1);
            }
            else
            {
                pcb_table[current_task]->priority = 0;
                pcb_table[current_task]->process_id = pid;
                HeapInsert(minHeap, *pcb_table[current_task]);
                HashMapPut(map, pcb_table[current_task]->process_id, current_task); // Maps the process id to the index in the pcb_table
                current_task++;
            }
        }

        if (getpid() == main_process_id)
        {

            if (minHeap->size == 0)
            {
                // No current process to run
                global_clock_sjf += 1;
                continue;
            }

            // Choose the next task to run
            int process_id = minHeap->arr[0].process_id;
            int process_index = HashMapGet(map, process_id);
            PCB *process = pcb_table[process_index];
            heapifyDown(minHeap, 0);

            process->remaining_time -= 1;
            global_clock_sjf += 1;

            if (process->remaining_time <= 0)
            {
                // Process has finished executing
                kill(process->process_id, SIGUSR2);
                minHeap->arr[0] = minHeap->arr[minHeap->size - 1];
                minHeap->size--;
                heapifyDown(minHeap, 0);
                process->completion_time = global_clock_sjf;
                process->turnaround_time = process->completion_time - process->arrival_time;
                process->waiting_time = process->completion_time - process->burst_time - process->arrival_time;
            }
        }
    } // End While Loop

    HashMapFree(map);
    return pcb_table;
}