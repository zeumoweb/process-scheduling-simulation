#pragma once
#include "pcb.h"
#include "utility_functions.h"
#include "queue.h"
#include "hashmap.h"
#include <stdio.h>
#include <stdlib.h>

PCB** mlfq_scheduler(char* filename, int time_quantum);
int isAllProcessesDone(PCB** pcb_table, int num_tasks);
int getPriorityOfNextQueue(Queue **queues);
void promoteAllProcesses(Queue **queues, PCB **pcb_table, HashMap *map);