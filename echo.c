#include "sish.h"


void echo(char** arguments)
{
	int i;

	for (i = 1; arguments[i] != NULL; i++) {
		printf("%s", arguments[i]);
		
		arguments[i] = NULL;

		if (arguments[i+1] != NULL) {
			printf(" ");
		}
	}

	printf("\n");
}

