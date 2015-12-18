#include "sish.h"


/*	
 *	Executes the provided command under the parameters specified. Our
 *	approach was inspired by StackOverflow thread 12679075.
 *	
 *	@param		char**		an array of command tokens
 *	@param		int		the number of pipe commands
 *	@param		int[]		pipe operators indexes
 *	@param		char*		input filename
 *	@param		char*		output filename
 *	@param		char		background process (boolean)
 *	@param		char*		file write mode ("w", "a")
 *	
 *	@return		void
 *	
 */
void command(char** args, int commands, int start[], char* in,
             char* out, char bg, char* mode)
{
	int i = 0;
	int pid;
	int status;
	int place;
	int j = 0;
	int q = 0;
	
	int pipes = commands-1;
	int pipefds[2*pipes];
	start[0] = 0;
	
	exit_status = 0;
	
	/*  */
	for (i = 0; i < pipes; i++)
	{
		if (pipe(pipefds + i * 2) == -1)
		{
			fprintf(stderr, "-%s: unable to create pipe: %s\n",
				getprogname(), strerror(errno)
			);
			return;
		}
	}
	
	/*  */
	for (i = 0; i < commands; i++)
	{
		place = start[i];
		
		if ((pid = fork()) == 0)
		{
			/* Child Process */
			
			/* If background process is set to true, then mark the
			 * child process as a daemon.
			 */
			if (bg)
			{
				daemon(1, 1);
			}
			
			/* if not last command */
			if (i < pipes)
			{
				if (dup2(pipefds[j + 1], 1) == -1)
				{
					fprintf(stderr,
						"-%s: dup2(2) failed: %s\n",
						getprogname(), strerror(errno)
					);
					exit(EXIT_FAILURE);
				}
			}
			
			/*  */
			if (j != 0)
			{
				if (dup2(pipefds[j - 2], 0) == -1)
				{
					fprintf(stderr,
						"-%s: dup2(2) failed: %s\n",
						getprogname(), strerror(errno)
					);
					exit(EXIT_FAILURE);
				}
			}
			
			/*  */
			for (q = 0; q < 2 * pipes; q++)
			{
				close(pipefds[q]);
			}
			
			/*  */
			if (in != NULL)
			{
				if (freopen(in, "r", stdin) == NULL)
				{
					fprintf(stderr,
						"-%s: unable to open input stream '%s': %s\n",
						getprogname(), in,
						strerror(errno)
					);
					/* exit here? */
				}
			}
			
			/*  */
			if (out != NULL)
			{
				if (freopen(out, mode, stdout) == NULL)
				{  
					fprintf(stderr,
						"-%s: unable to write to output stream '%s': %s\n",
						getprogname(), out,
						strerror(errno)
					);
					/* exit here? */
				}
			}
			
			/*  */
			if (execvp(args[place], args + place) < 0)
			{
				perror(*args);
				exit(EXIT_FAILURE);
			}
		}
		else if (pid > 0)
		{
			/* Parent */
			/*if (wait(&exit_status) == -1)
			{
				fprintf(stderr, "-%s: wait(2) failed\n",
					getprogname()
				);
				return;
			}*/
		}
		else if (pid == -1)
		{
			fprintf(stderr, "-%s: unable to fork process: %s\n",
				getprogname(), strerror(errno)
			);
			return;
		}

		j += 2;
	}
	
	/*  */
	for (i = 0; i < 2 * pipes; i++)
	{
		close(pipefds[i]);
	}
	
	/*  */
	for (i = 0; i < pipes + 1; i++)
	{
		wait(&status);
	}
}
