SRC = fcfs_policy.c hashmap.c heap.c sjf_preemptive.c error_handler.c pcb.c mlfq_policy.c queue.c utility_functions.c round_robin_policy.c scheduler.c 
CC = gcc
OBJ = $(SRC:.c=.o)
EXEC = program

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.c
	$(CC) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)


