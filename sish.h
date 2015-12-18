#ifndef _SISH_H_
#define _SISH_H_

#include <stdio.h>
#include <stdlib.h>

#ifndef __NetBSD__
#include <bsd/stdlib.h>
#endif

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

#ifndef MAXCOMMANDS
#define MAXCOMMANDS 512
#endif


/* sish.c */
char* shell_prompt;
int   tracing_enabled;
char* arguments_command;
int   process_id;
int   exit_status;

int  main(int, char**);
void set_shell(char*);
void parse_arguments(int, char**);
void sigint_handler(int);

/* parser.c */
char** parse(char*);

/* eval.c */
void eval(char **,int);
int  count_pipes(char** arglist);

/* cd.c */
void cd(char**);

/* echo.c */
void echo(char**);

/* command.c */
void command(char**,int,int[], char*, char*, char, char*);

#endif
