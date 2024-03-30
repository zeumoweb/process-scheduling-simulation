#include "utility_functions.h"
#define CHANCE_OF_IO_REQUEST 10
#define CHANCE_OF_IO_COMPLETE 4

void splitLine(char *line, int *num1, int *num2, int *num3, int *num4)
{
    // Using strtok to split the line at ":"
    char *token = strtok(line, ":");

    // Converting tokens to integers and saving them in variables
    *num1 = atoi(token);

    token = strtok(NULL, ":");
    *num2 = atoi(token);

    token = strtok(NULL, ":");
    *num3 = atoi(token);

    token = strtok(NULL, ":");
    *num4 = atoi(token);
}

int getNumLinesInFile(char *file_name)
{
    FILE *file = fopen(file_name, "r");
    char *line;
    size_t length;
    int num_tasks = 0;
    while ((line = fgetln(file, &length)))
    {
        num_tasks++;
    }
    return num_tasks;
}

// Read Process from the text file and load them into memory
PCB **process_input_file(char *file_name, HashMap *map)
{
    FILE *file = fopen(file_name, "r");
    int process_id, arrival_time, burst_time, priority;
    if (file == NULL)
    {
        perror("Failed to open input file. Provide the right file path/name");
        exit(1);
    }
    char *line;
    size_t length;

    int num_tasks = getNumLinesInFile(file_name);
    int process_ids[num_tasks];
    PCB **pcb_table = (PCB **)malloc(sizeof(PCB *) * num_tasks);

    if (pcb_table == NULL)
    {
        perror("Failed to allocate memory for PCB table");
        exit(1);
    }

    for (int i = 0; i < num_tasks; i++)
    {
        pcb_table[i] = (PCB *)malloc(sizeof(PCB));
        if (pcb_table[i] == NULL)
        {
            perror("Failed to allocate memory for PCB");
            exit(1);
        }
    }

    int i = 0;
    while ((line = fgetln(file, &length)))
    {
        line[strcspn(line, "\n")] = '\0';
        splitLine(line, &process_id, &arrival_time, &burst_time, &priority);
        initializePCB(pcb_table[i], process_id, arrival_time, burst_time, priority);
        HashMapPut(map, process_id, i); // Maps the process id to the index in the pcb_table
        i++;
    }

    return pcb_table;
}

void printStatistics(PCB **pcb_table, int num_tasks, char *policy)
{
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int total_response_time = 0;
    int total_completion_time = 0;
    int longest = 0;
    int shortest = INT16_MAX;
    printf("\n");
    printf("+-------+-----------------+-----------------+-------------+------------------+---------------------+--------------------+----------------------+ \n");
    printf("| Job#  | Arrival Time    | Burst Time      | Priority    | Waiting Time     | Turnaround Time     | Response Time    | Completion Time        | \n");
    printf("+-------+-----------------+-----------------+-------------+------------------+---------------------+--------------------+----------------------+ \n");

    for (int i = 0; i < num_tasks; i++)
    {
        printf("|  %-3d  |     %-6d       |    %-6d      |   %-6d     |     %-6d       |       %-6d        |     %-6d        |       %-6d        |\n",
               pcb_table[i]->process_id, pcb_table[i]->arrival_time, pcb_table[i]->burst_time, pcb_table[i]->priority,
               pcb_table[i]->waiting_time, pcb_table[i]->turnaround_time, pcb_table[i]->response_time, pcb_table[i]->completion_time);

        total_waiting_time += pcb_table[i]->waiting_time;
        total_turnaround_time += pcb_table[i]->turnaround_time;
        total_response_time += pcb_table[i]->response_time;
        total_completion_time += pcb_table[i]->completion_time;
        if (pcb_table[i]->completion_time > longest)
        {
            longest = pcb_table[i]->completion_time;
        }
        if (pcb_table[i]->completion_time < shortest)
        {
            shortest = pcb_table[i]->completion_time;
        }
    }
    printf("\n");
    printf("Scheduling Policy: %s\n", policy);
    printf("Number of JOBS: %d\n", num_tasks);
    printf("Total Simulation Time: %d\n", longest);
    printf("Shortest Job Completion Time: %d\n", shortest);
    printf("Longest Job Completion Time: %d\n", longest);
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / num_tasks);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / num_tasks);
    printf("Average Response Time: %.2f\n", (float)total_response_time / num_tasks);
}

int IO_request()
{
    if (rand() % CHANCE_OF_IO_REQUEST == 0)
        return 1;
    else
        return 0;
}

int IO_complete()
{

    if (rand() % CHANCE_OF_IO_COMPLETE == 0)
        return 1;
    else
        return 0;
}