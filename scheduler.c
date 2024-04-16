#include "pcb.h"
#include "utility_functions.h"
#include "round_robin_policy.h"
#include "fcfs_policy.h"
#include "sjf_preemptive.h"
#include "mlfq_policy.h"
#include "queue.h"

int main(int argc, char** argv){

    srand(time(NULL)); // Seed the random number generator
    int num_tasks = getNumLinesInFile("jobs_data2.txt");
    // PCB** tasks = fcfs_scheduler("jobs_data2.txt"); 
    // PCB** tasks = round_robin_scheduler("jobs_data2.txt", 1);
   PCB** tasks =  sjf_preemptive("jobs_data2.txt");
    printStatistics(tasks, num_tasks, "round robin");
    printf("Done %d \n", num_tasks);
    
    return 0;
}