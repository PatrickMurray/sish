#include "command.h"


void command_execute(char* command) {
	char** tokens;
	
	tokens = tokenize(command);
	
	if (valid_token_sequence(tokens) < 0) {
		fprintf(stderr, "%s: malformed command '%s'\n",
			getprogname(), command
		);
		return;
	}
	
	free(tokens);

	printf("Executing: '%s'\n", command);
}
