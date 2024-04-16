#include "mlfq_policy.h"

#define MAX_ALLOTMENT_TIME 5 // Time quantum for each priority level
#define MAX_PRIORITY 5       // Number of priority levels
#define AGING_THRESHOLD 10   // Number of global_clock cycles before all processes are promoted back to the topmost priority level

pid_t main_process_id;
int global_clock = 0; // global_clock


void promoteAllProcesses(Queue **queues, PCB **pcb_table, HashMap *map){
    for (int i = 1; i < MAX_PRIORITY; i++)
        {
            while (QueueEmpty(queues[i]) == 0)
            {
                int process_id = QueuePop(queues[i]);
                int process_index = HashMapGet(map, process_id);
                pcb_table[process_index]->priority = 0;
                pcb_table[process_index]->current_allotment = 0;
                QueuePush(queues[0], process_id);
            }
        }
}


int getPriorityOfNextQueue(Queue **queues)
{
    int priority = -1;
    for (int i = 0; i < MAX_PRIORITY; i++)
    {
        if (QueueEmpty(queues[i]) == 0)
        {
            return priority = i;
        }
    }
    return priority;
}


PCB** mlfq_scheduler(char *filename, int quantum)
{
    main_process_id = getpid();
    HashMap *map = HashMapCreate();                                    // Maps the process id to the index in the pcb_table
    Queue **queues = (Queue **)malloc(MAX_PRIORITY * sizeof(Queue *)); // Initialize the priority queues
    for (int i = 0; i < MAX_PRIORITY; i++)
    {
        queues[i] = QueueCreate();
    }

    PCB **pcb_table = process_input_file(filename); // Load the tasks into memory
    int num_tasks = getNumLinesInFile(filename);         // Get the number of tasks in the file
    Queue *input_output_queue = QueueCreate();           // Initialize the input/output queue

    bubble_sort(pcb_table, num_tasks, map); // Sort the tasks based on arrival time and process ID

    int current_task = 0;
    while (isAllProcessesDone(pcb_table, num_tasks) == 0)
    {
        // Check all the processes that have completed IO execution and add them to ready queues
        int size_input_queue = QueueSize(input_output_queue);
        for (int i = 0; i < size_input_queue; i++)
        {
            if (IO_complete() == 1)
            {
                int process_id = QueuePop(input_output_queue);
                int process_index = HashMapGet(map, process_id);
                PCB *process = pcb_table[process_index];
                QueuePush(queues[process->priority], process_id);
            }
        }

        // Check all the processes that have arrived and add them to the topmost  queue
        while (current_task < num_tasks && pcb_table[current_task]->arrival_time <= global_clock)
        {
            pid_t pid = fork();
            if (pid == 0 ){
                // child process
                kill(getpid(), SIGUSR1);
            } else {
                pcb_table[current_task]->priority = 0;
                    pcb_table[current_task]->process_id = pid;
                    QueuePush(queues[0], pcb_table[current_task]->process_id);
                    HashMapPut(map, pcb_table[current_task]->process_id, current_task); // Maps the process id to the index in the pcb_table
                    current_task++;
            }
            
        }

        if (getpid() == main_process_id)
        {
          
        // Choose the next queue to run
        int priority = getPriorityOfNextQueue(queues);
        if (priority == -1)
        {
            global_clock += 1;
            continue;
        }

        // Start Round Robin On The current Queue Level
        int queue_size = QueueSize(queues[priority]);
        for (int i = 0; i < queue_size; i++)
        {
            // Start Round Robin on the current queue level
            int process_id = QueuePeek(queues[priority]);
            int process_index = HashMapGet(map, process_id);
            PCB *process = pcb_table[process_index];
            for (int j = 0; j < quantum; j++)
            {
                process->remaining_time -= 1;
                process->current_allotment += 1;
                global_clock += 1;

                // if (IO_request() == 1){
                //     // Current Process Perform and IO Request
                //     QueuePush(input_output_queue, process->process_id);
                //     break;
                // }
                
                if (process->remaining_time <= 0)
                {
                    // Process has finished executing
                    kill(process->process_id, SIGUSR2);
                    QueuePop(queues[priority]);
                    process->completion_time = global_clock;
                    process->turnaround_time = process->completion_time - process->arrival_time;
                    process->waiting_time = process->completion_time - process->burst_time - process->arrival_time;
                    break;

                }
            
            }
            if (process->remaining_time <= 0){
                // Process has finished executing
                continue;
            }

            if (process->current_allotment >= MAX_ALLOTMENT_TIME && priority < MAX_PRIORITY - 1)
                {
                    // Process has not finished executing but has used up its time allotment
                    // Move the process to the next priority level
                    process->current_allotment = 0;
                    process->priority = priority + 1;
                    QueuePop(queues[priority]);
                    QueuePush(queues[priority + 1], process->process_id);
                    break;
                }
            else{
                process_id = QueuePop(queues[priority]);
                QueuePush(queues[priority], process_id);
            }
            
        } // End Round Robin Round
    
    // After some time period, move all the process back to the topmost priority level to avoid starvation
    if (global_clock % AGING_THRESHOLD == 0)
    {
        promoteAllProcesses(queues, pcb_table, map);
    }
    }} // End While Loop

    // Free All Queues
    for (int i = 0; i < MAX_PRIORITY; i++)
    {
        QueueFree(queues[i]);
    }
    HashMapFree(map);
    return pcb_table;
}