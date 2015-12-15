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

#define maxargs 15
#define MAXCOMMANDS 512

char* _args[maxargs];

int tracing_enabled;
char* arguments_command;

void eval(char **);
char** parse(char*);
void cd(char**);
void echo(char**);

#endif
