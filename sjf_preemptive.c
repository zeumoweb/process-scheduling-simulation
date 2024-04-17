#include "sjf_preemptive.h"

pid_t main_process_id_sjf;
int global_clock_sjf = 0; // global_clock_

PCB **sjf_preemptive(char *filename)
{
    main_process_id_sjf = getpid();

    HashMap *map = HashMapCreate();                 // Maps the process id to the index in the pcb_table
    PCB **pcb_table = process_input_file(filename); // Load the tasks into memory
    int num_tasks = getNumLinesInFile(filename);    // Get the number of tasks in the file

    MinHeap *minHeap = createMinHeap(num_tasks); // Initialize the min heap

    bubble_sort(pcb_table, num_tasks, map); // Sort the tasks based on arrival time and process ID

    int current_task = 0;
    int prev = -1;
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

        if (getpid() == main_process_id_sjf)
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
            if (process->remaining_time == process->burst_time)
            {
                process->response_time += global_clock_sjf - process->arrival_time;
            }

            process->remaining_time -= 1;
            minHeap->arr[0].remaining_time -= 1;
            heapifyDown(minHeap, 0);
            global_clock_sjf += 1;
            if (prev != process_id && prev != -1)
            {
                printf("Proceess %d was preempted at time %d\n", prev, global_clock_sjf);
            }
            prev = process_id;
            printf("Proceess %d is executing at time %d \n", process_id, global_clock_sjf);

            if (process->remaining_time <= 0)
            {
                // Process has finished executing
                printf("Proceess %d completed execution at time %d \n", process_id, global_clock_sjf);
                prev = -1;
                kill(process->process_id, SIGUSR2);
                minHeap->arr[0] = minHeap->arr[minHeap->size - 1];
                minHeap->size--;
                for (int i = 0; i < minHeap->size; i++)
                {
                    printf("Process %d has remaining time %d\n", minHeap->arr[i].process_id, minHeap->arr[i].remaining_time);
                }
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