#include "utility_functions.h"


void splitLine(char *line, int *num1, int *num2, int *num3, int *num4) {
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


int getNumLinesInFile(char* file_name){
    FILE* file = fopen(file_name, "r");
    char* line;
    size_t length;
    int num_tasks = 0;
    while ((line = fgetln(file, &length))){
        num_tasks ++;
    }
    return num_tasks;
}


// Read Process from the text file and load them into memory
PCB** process_input_file(char* file_name){
    FILE* file = fopen(file_name, "r");
    int process_id, arrival_time, burst_time, priority;
    if (file == NULL){
        perror("Failed to open input file. Provide the right file path/name");
        exit(1);
            }
    char* line;
    size_t length;

    int num_tasks = getNumLinesInFile(file_name);
    int process_ids[num_tasks];
    PCB** pcb_table = (PCB**)malloc(sizeof(PCB*) * num_tasks);
    if (pcb_table == NULL){
        perror("Failed to allocate memory for PCB table");
        exit(1);
    }
    

    while ((line = fgetln(file, &length))){
        line[strcspn(line, "\n")] = '\0';
        splitLine(line, &process_id, &arrival_time, &burst_time, &priority);
        initializePCB(pcb_table[process_id], process_id, arrival_time, burst_time, priority);
        process_ids[num_tasks] = process_id;
        num_tasks ++;
    }

    for (int i = 0; i < num_tasks; i ++){
        printf("%d and %d and %d and %d \n", pcb_table[process_ids[i]]->process_id, pcb_table[process_ids[i]]->arrival_time, pcb_table[process_ids[i]]->burst_time, pcb_table[process_ids[i]]->priority);
    }

    return pcb_table;

}