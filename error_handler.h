#pragma once
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void handle_segfault(int sig);
void handle_int(int sig);
void handle_file_error(int sig);