#include "shell.h"

#ifndef COMMAND_MAX_LENGTH
#define COMMAND_MAX_LENGTH 65536
#endif


void shell_start() {
	char* command;
	
	if ((command = calloc(COMMAND_MAX_LENGTH, sizeof(char))) == NULL) {
		fprintf(stderr, "%s: unable to allocate memory!\n",
			getprogname()
		);
		exit(EXIT_FAILURE);
	}
	
	while (strcmp(command, "exit") != 0) {
		bzero(command, COMMAND_MAX_LENGTH);
		
		printf("$ ");
		fgets(command, COMMAND_MAX_LENGTH, stdin);
		
		/* Remove the newline at the end of the command */
		command[strlen(command)-1] = '\0';
		
		if (strlen(command) > 0) {
			command_execute(command);
		}
	}
	
	free(command);
}
