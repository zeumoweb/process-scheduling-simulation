#include "pcb.h"
#include "utility_functions.h"
#include "round_robin_policy.h"
#include "queue.h"

int main(int argc, char** argv){
    // int clock = 0; // Initialize Clock

    // HashMap* map = HashMapCreate(); // Maps the process id to the index in the pcb_table
    // Queue* ready_queue = QueueCreate(); // Initialize the ready queue

    // PCB** tasks = process_input_file("jobs_data1.txt", map); // Load the tasks into memory
    // int num_tasks = getNumLinesInFile("jobs_data1.txt"); // Get the number of tasks in the file
    // int current_task = 0; 
    // while (num_tasks > 0 || QueueEmpty(ready_queue) == 0){
    //     // While there are tasks to be processed or tasks in the ready queue
    //     if (QueueEmpty(ready_queue) == 1){
    //         // If the ready queue is empty, add the next task to the ready queue
    //         QueuePush(ready_queue, tasks[current_task]->process_id);
    //         clock = tasks[current_task]->arrival_time;
    //         current_task ++;
    //         num_tasks --;
    //     }


    // }
    srand(time(NULL)); // Seed the random number generator
    int num_tasks = getNumLinesInFile("jobs_data1.txt");
    PCB** tasks = round_robin_scheduler("jobs_data1.txt", 10);
    printStatistics(tasks, num_tasks, "Round Robin");
    
    return 0;
}