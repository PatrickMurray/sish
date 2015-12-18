#include "sish.h"


/*	
 *	Parses the provided command string and tokenizes it by delimiting
 *	spaces, tabs, and newlines.
 *	
 *	@param		char*		a command
 *	
 *	@return		char**		command token sequence
 *	
 */
char** parse(char* command)
{
	char** tokens;
	char*  delimiters;
	int    idx;
	char*  token;
	
	if ((tokens = calloc(MAXCOMMANDS, sizeof(char*))) == NULL)
	{
		fprintf(stderr, "-%s: unable to allocate memory\n",
			getprogname()
		);
		exit(EXIT_FAILURE);
	}
	
	delimiters = " \t\n";
	idx = 0;
	token = strtok(command, delimiters);
	
	while (token != NULL)
	{
		tokens[idx] = token;
		idx++;
		token = strtok(NULL, delimiters);
	}
	
	return tokens;
}
