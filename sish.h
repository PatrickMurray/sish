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


#define maxargs     15
#define MAXCOMMANDS 512


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



char* _args[maxargs];


/* parser.c */


/* eval.c */
void eval(char **,int);
int count_pipes(char** arglist);


/* cd.c */
void cd(char**);


/* echo.c */
void echo(char**);


/* command.c */
void command(char**,int,int[], char*, char*, char, char*);




int num_commands;

char** parse(char*);


#endif
