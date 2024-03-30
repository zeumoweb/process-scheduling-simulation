#pragma once
#include <stdlib.h> 
#include <stdio.h>
#include <string.h>
#include "pcb.h"

void splitLine(char *line, int *num1, int *num2, int *num3, int *num4);
int getNumLinesInFile(char* file_name);
PCB** process_input_file(char* file_name);