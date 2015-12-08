#include "tokenization.h"


char* tokenize_operators(char* command) {
	return "hello world";
}


char** tokenize_string(char* command) {
	char** tokens;
	
	if ((tokens = calloc(1, sizeof(char*))) == NULL) {
		fprintf(stderr, "%s: unable to allocate memory\n",
			getprogname()
		);
		exit(EXIT_FAILURE);
	}
	
	return tokens;
}
