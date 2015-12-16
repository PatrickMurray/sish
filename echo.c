#include "sish.h"


/*	
 *	A builtin implementation of the echo command.
 *	
 *	@param		char**		argumenta
 *	
 *	@return		void
 *	
 */
void echo(char** arguments)
{
	int i;
	
	for (i = 1; arguments[i] != NULL; i++) {
		/* Print each argument */
		printf("%s", arguments[i]);
		
		/* Clear them */
		arguments[i] = NULL;
		
		/* If the next argument isn't null append a space to the end.*/
		if (arguments[i+1] != NULL) {
			printf(" ");
		}
	}
	
	printf("\n");
}

