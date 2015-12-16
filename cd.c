#include "sish.h"


/*	
 *	An implementation of the cd builtin command.
 *	
 *	@param		char**		arguments
 *	
 *	@return		void
 */
void cd(char** args)
{
	char* directory;
	int error;
	struct passwd *user;
	int i;
	
	directory = args[1];
	error = 0;

	if(directory == NULL)
	{
		/* If the user provides no directory, look up their home. */
		if((user = getpwuid(getuid())) == NULL)
		{
			fprintf(stderr, "cd: getpwuid() error: %s\n",
				strerror(errno)
			);
			error = 1;
		}

		if (!error)
		{
			directory = user->pw_dir;
		}
	}
	
	if (!error)
	{
		if(chdir(directory) == -1)
		{
			fprintf(stderr, "cd %s: %s\n", directory,
				strerror(errno)
			);
		}
	}
	
	/* Clear up the arguments. */
	for (i = 0; args[i] != NULL; i++)
	{
		args[i] = NULL;
	}
}
