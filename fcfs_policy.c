#include "fcfs_policy.h"

PCB **fcfs_scheduler(char *filename)
{

   int clock = 0; // Initialize Clock

   HashMap *map = HashMapCreate();     // Maps the process id to the index in the pcb_table
   PCB **pcb_table = process_input_file(filename, map); // Load the tasks into memory
   int num_tasks = getNumLinesInFile(filename);         // Get the number of tasks in the file

   for (int i = 0; i < num_tasks; i++)
   {
      PCB *process = pcb_table[i];
      if (process->arrival_time > clock)
      {
         clock = process->arrival_time;
      }
      process->response_time += clock - process->arrival_time;
      process->remaining_time -= process->burst_time;
      clock += process->burst_time;

      process->completion_time = clock;
      process->turnaround_time = process->completion_time - process->arrival_time;
      process->waiting_time = process->completion_time - process->burst_time - process->arrival_time;
   }

   return pcb_table;
}