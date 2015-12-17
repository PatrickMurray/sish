#include "sish.h"


/*	
 *	An implementation of the cd builtin command.
 *	
 *	@param		char**		arguments
 *	
 *	@return		void
 */
void cd(char** argv)
{
	char*          directory;
	int            error;
	struct passwd* user;
	int            i;
	
	/* First, attempt to set the target directory to the first argument */
	directory = argv[1];
	error = 0;
	
	/* If the user does not provide a directory in argv[1] */
	if(directory == NULL)
	{
		/* Look up the user's home directory */
		if((user = getpwuid(getuid())) == NULL)
		{
			fprintf(stderr, "cd: getpwuid() error: %s\n",
				strerror(errno)
			);
			/* If an error occurs, we want to mark it as occuring
			 * and then reset args before exiting.
			 */
			error = 1;
		}
		
		if (!error)
		{
			directory = user->pw_dir;
		}
	}
	
	if (!error)
	{
		/* If we're unable to change the directory, inform the user */
		if(chdir(directory) == -1)
		{
			fprintf(stderr, "cd %s: %s\n", directory,
				strerror(errno)
			);
			error = 1;
		}
	}
	
	/* As mentioned previously, when an error occurs, we must clear out
	 * args and thus we cannot simply exit().
	 */
	for (i = 0; argv[i] != NULL; i++)
	{
		argv[i] = NULL;
	}
}
