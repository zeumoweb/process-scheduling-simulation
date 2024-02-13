# CPU Process Scheduling Simulation

## Input Format

The input format for the simulator is a text file which contains information about each process. The information include the process ID, Arrival Time, Burst Time, and Priority. Priority will be ignored for scheduler policies such as Round Robins and First Come First Served since they don't utilize process priority during scheduling.

Each line within the input text will represent information about one job and it will follow the following format:

Process Id : Arrival time : Burst time : Priority

Example input:
* 13:0:17:1
* 123:3:10:3
* 4:1:20:2

Describes a simulation that has three jobs.

The first job has a process ID of 13, an arrival time of 0 (when the simulation starts), it needs to do 17 clock ticks of work, and has an priority of 1.

