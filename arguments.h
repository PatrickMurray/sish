#include <stdio.h>
#include <stdlib.h>
#include <bsd/stdlib.h>
#include <unistd.h>


int   tracing_enabled;
char* arguments_command;

void parse_arguments(int, char**);
