#include "sish.h"


/*	
 *	A builtin implementation of the echo command.
 *	
 *	@param		char**		argumenta
 *	
 *	@return		void
 *	
 */
void echo(char** argv)
{
	int i;
	
	/* Iterate through argv, printing arguments and then clearing them for
	 * the next command.
	 */
	for (i = 1;
	     argv[i] != NULL;
	     i++)
	{
		printf("%s", argv[i]);

		/* If there is an argument following the current argument, we
		 * want to add a space between them.
		 */
		if (arguments[i + 1] != NULL) {
			printf(" ");
		}

		/* Reset argv as we iterate through */
		argv[i] = NULL;
	}
	
	printf("\n");
}

