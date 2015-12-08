#include "arguments.h"


void parse_arguments(int argc, char** argv) {
	char flag;
	
	tracing_enabled   = 0;
	arguments_command = NULL;
	
	/* Override getopt() error messages */
	opterr = 0;

	while ((flag = getopt(argc, argv, ":xc:")) >= 0) {
		switch (flag) {
			case 'x':
				tracing_enabled = 1;
				break;
			case 'c':
				arguments_command = optarg;
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

	printf("DEBUGGING\n");
	printf("---------\n");
	printf("tracing_enabled   = %i\n", tracing_enabled);
	printf("arguments_command = %s\n", arguments_command);
}
