#include "pcb.h"
#include "utility_functions.h"
#include "round_robin_policy.h"
#include "fcfs_policy.h"
#include "sjf_preemptive.h"
#include "mlfq_policy.h"
#include "queue.h"

int main(int argc, char** argv){

    srand(time(NULL)); // Seed the random number generator

    // BINDING SIGNALS TO CORRESPONDING HANDLERS
    signal(SIGINT, handle_error);
    signal(SIGSEGV, handle_error);
    signal(SIGUSR1, execute_process);
    signal(SIGUSR2, execute_process);
    char* job_data_file = argv[1];
    int scheduling_policy = atoi(argv[2]);
    int num_tasks = getNumLinesInFile("jobs_data1.txt");
    if (scheduling_policy == 1){
        PCB** tasks = fcfs_scheduler(job_data_file);
        printStatistics(tasks, num_tasks, "fcfs");
    }
    else if (scheduling_policy == 2){
        int quantum = atoi(argv[3]);
        PCB** tasks = round_robin_scheduler(job_data_file, quantum);
        printStatistics(tasks, num_tasks, "round robin");
    }
    else if (scheduling_policy == 3){
        PCB** tasks = sjf_preemptive(job_data_file);
        printStatistics(tasks, num_tasks, "sjf preemptive");
    }
    else if (scheduling_policy == 4){
        int time_quantum = atoi(argv[3]);
        PCB** tasks = mlfq_scheduler(job_data_file, time_quantum);
        printStatistics(tasks, num_tasks, "mlfq");
    }
    else{
        printf("Invalid scheduling policy\n");
    }

    printf("Exiting... Simulation Completed\n\n");
    return 0;
}