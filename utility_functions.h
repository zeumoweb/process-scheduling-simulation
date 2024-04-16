#pragma once
#include <stdlib.h> 
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "pcb.h"
#include "hashmap.h"
#include <time.h>
#include "error_handler.h"

void splitLine(char *line, int *num1, int *num2, int *num3, int *num4);
int getNumLinesInFile(char* file_name);
PCB** process_input_file(char* file_name, HashMap* map);
void printStatistics(PCB** pcb_table, int num_tasks, char* policy_name);
int IO_request();
int IO_complete();
void handle_error(int sig);
void execute_process(int sig);