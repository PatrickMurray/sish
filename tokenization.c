#include "tokenization.h"


char** tokenize(char* command) {
	char** tokens;
	
	if ((tokens = calloc(2, sizeof(char*))) == NULL) {
		fprintf(stderr, "%s: unable to allocate memory!\n",
			getprogname()
		);
		exit(EXIT_FAILURE);
	}

	tokens[0] = "hello";
	tokens[1] = "world";

	return tokens;
}


int valid_token_sequence(char** tokens) {
	return 0;
}
