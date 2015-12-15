#include "sish.h"


void echo(char** arguments)
{
	int i;

	/* Replace $? and $$ */
	for (i = 1; arguments[i] != NULL; i++) {
		printf("<%s>\n", arguments[i]);
		if (strcmp(arguments[i], "$?") == 0)
		{
			printf("Exit Status");
			//printf("%i", );
		}
		else if (strcmp(arguments[i], "$$") == 0)
		{
			printf("Current PID");
			//printf("%i", );
		}
		else
		{
			printf("%s", arguments[i]);
		}

		if (arguments[i+1] != NULL) {
			printf(" ");
		}

		arguments[i] = NULL;
	}
	printf("\n");
}
