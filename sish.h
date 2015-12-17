#ifndef _SISH_H_
#define _SISH_H_

#include <stdio.h>
#include <stdlib.h>
#include <bsd/stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <pwd.h>
#include <errno.h>
#include <string.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/wait.h>

#define maxargs     15
#define MAXCOMMANDS 512
#define BUFFER_SIZE 65536

char* _args[maxargs];

int tracing_enabled;
char* arguments_command;

int exit_status;
int process_id;

int num_commands;

void eval(char **,int);
char** parse(char*);
void cd(char**);
void echo(char**);

void command(char**, char*, char*, char, char*);

#endif
