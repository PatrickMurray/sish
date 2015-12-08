#include <stdio.h>
#include <stdlib.h>
#include <bsd/stdlib.h>

#include "arguments.h"


int main(int argc, char** argv) {
	setprogname(argv[0]);
	
	parse_arguments(&argc, argv);
	
	return EXIT_SUCCESS;
}
