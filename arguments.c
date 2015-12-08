#include "arguments.h"


void parse_arguments(int* argc, char** argv) {
	char flag;
	
	/* Override getopt() error messages */
	//opterr = 0;

	while ((flag = getopt(*argc, argv, "xc:")) >= 0) {
		switch (flag) {
			case 'x':
				break;
			case 'c':
				break;
			case ':':
				fprintf(stderr,
					"%s: -%c requires an argument\n",
					getprogname(), optopt
				);
				exit(EXIT_FAILURE);
			case '?':
			default:
				fprintf(stderr, "%s: unknown flag -%c\n",
					getprogname(), optopt
				);
				exit(EXIT_FAILURE);
		}
	}
}

/*
void arguments_set_default() {
	
}
*/
