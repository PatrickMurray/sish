#include "sish.h"


/*	
 *	Executes the provided command under the parameters specified. Our
 *	approach was inspired by StackOverflow thread 12679075.
 *	
 *	@param		char**		an array of command tokens
 *	@param		int		the number of pipes
 *	@param		int[]		pipe operators indexes
 *	@param		char*		input filename
 *	@param		char*		output filename
 *	@param		char		background process (boolean)
 *	@param		char*		file write mode ("w", "a")
 *	
 *	@return		void
 *	
 */
void command(char** args, int pipes, int pipe_pos[], char* input_file,
             char* output_file, char background, char* mode)
{
	int   i;
	int   j;
	int   k;
	int*  pipe_fds;
	int   place;
	pid_t pid;
	
	/* Allocate two file descriptors for each pipe, input and output. */
	if ((pipe_fds = calloc(2 * pipes, sizeof(int))) == NULL)
	{
		fprintf(stderr, "-%s: unable to allocate memory\n",
			getprogname()
		);
		return;
	}
	
	pipe_pos[0] = 0;
	
	/* Our initial exit status will be 0 prior to execution. */
	exit_status = 0;
	
	/* Occupy the pipe array */
	for (i = 0; i < pipes; i++)
	{
		if (pipe(pipe_fds + i * 2) == -1)
		{
			fprintf(stderr, "-%s: unable to create pipe: %s\n",
				getprogname(), strerror(errno)
			);
			return;
		}
	}
	
	/* Iterate through every command */
	for (i = 0, j = 0; i < pipes + 1; i++, j += 2)
	{
		/* Look up the location of the next pipe */
		place = pipe_pos[i];
		
		if ((pid = fork()) == 0)
		{
			/* Child Process */
			
			/* If background process is set to true, then mark the
			 * child process as a daemon.
			 */
			if (background)
			{
				if (daemon(1, 1) == -1)
				{
					fprintf(stderr,
						"-%s: daemon(3) failed: %s\n",
						getprogname(), strerror(errno)
					);
					exit(EXIT_FAILURE);
				}
			}
			
			/* While there are still pipe commands remaining, route
			 * the output of this command to the input of the next
			 * pipe command.
			 */
			if (i < pipes)
			{
				if (dup2(pipe_fds[j + 1], STDOUT_FILENO) == -1)
				{
					fprintf(stderr,
						"-%s: dup2(2) failed: %s\n",
						getprogname(), strerror(errno)
					);
					exit(EXIT_FAILURE);
				}
			}
			
			/* Route the input of this child process to be the
			 * output of the previous process.
			 */
			if (j != 0)
			{
				if (dup2(pipe_fds[j - 2], STDIN_FILENO) == -1)
				{
					fprintf(stderr,
						"-%s: dup2(2) failed: %s\n",
						getprogname(), strerror(errno)
					);
					exit(EXIT_FAILURE);
				}
			}
			
			for (k = 0; k < 2 * pipes; k++)
			{
				close(pipe_fds[k]);
			}
			
			/* Input Redirection */
			if (input_file != NULL)
			{
				if (freopen(input_file, "r", stdin) == NULL)
				{
					fprintf(stderr,
						"-%s: unable to open input stream '%s': %s\n",
						getprogname(), input_file,
						strerror(errno)
					);
					exit(EXIT_FAILURE);
				}
			}
			
			/* Output Redirection */
			if (output_file != NULL)
			{
				if (freopen(output_file, mode, stdout) == NULL)
				{  
					fprintf(stderr,
						"-%s: unable to write to output stream '%s': %s\n",
						getprogname(), output_file,
						strerror(errno)
					);
					exit(EXIT_FAILURE);
				}
			}
			
			/* Finally, attempt to execute the command. */
			if (execvp(args[place], args + place) == -1)
			{
				fprintf(stderr,
					"-%s: command execution error: %s\n",
					getprogname(), strerror(errno)
				);
				exit(EXIT_FAILURE);
			}
		}
		else if (pid == -1)
		{
			fprintf(stderr, "-%s: unable to fork process: %s\n",
				getprogname(), strerror(errno)
			);
			return;
		}
	}
	
	/* Close up all the open pipes */
	for (i = 0; i < 2 * pipes; i++)
	{
		close(pipe_fds[i]);
	}
	
	/* Set the previous command's exit status */
	for (i = 0; i < pipes + 1; i++)
	{
		wait(&exit_status);
	}

	free(pipe_fds);
}
