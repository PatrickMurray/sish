#include <stdio.h>
#include <stdlib.h>
#include <bsd/stdlib.h>

#include "arguments.h"
#include "tokenization.h"


int main(int argc, char** argv) {
	setprogname(argv[0]);
	
	parse_arguments(argc, argv);
	
	if (arguments_command != NULL) {
		tokenize_operators(arguments_command);
	}

	return EXIT_SUCCESS;
}
