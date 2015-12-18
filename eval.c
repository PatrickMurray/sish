#include "sish.h"


/*	
 *	Evaluates the provided array of commands.
 *	
 *	@param		char**		an array of commands
 *	@param		int		the number of pipes contained
 *	
 *	@return		void
 *	
 */
void eval(char** args, int pipes)
{
	int    idx;
	int    pos;
	char*  inputfile;
	char*  outputfile;
	char*  mode;
	char   background;
	int    command_start[MAXCOMMANDS];
	char** tmp;
	char*  curr_command;
	char*  new_args[MAXCOMMANDS];
	int    num_commands;
	
	inputfile        = NULL;
	outputfile       = NULL;
	mode             = "w";
	background       = 0;
	command_start[0] = 0;
	tmp              = new_args;
	num_commands     = pipes + 1;
	
	if (*args == NULL)
	{
		return;
	}
	
	/* If tracing is enabled, we must prepend "+ " before commands. */
	if (tracing_enabled)
	{
		fprintf(stderr, "+ ");
	}
	
	/* Iterate through the list of command tokens and evaulate the
	 * command's logic.
	 */
	for (idx = 0, pos = 1; args[idx] != NULL; idx++)
	{
		/* Once again, if tracing is enabled, we must print each
		 * command appended by "+ ". If a pipe is encountered, we also
		 * append a new line as well as "+ "
		 */
		if (tracing_enabled)
		{
			if (strcmp(args[idx], "|") == 0)
			{
				fprintf(stderr, "\n+ ");
			}
			else
			{
				fprintf(stderr, "%s", args[idx]);
				
				/* If the next element in the command token is
				 * neither NULL nor equal to "|" then we also
				 * append a space.
				 */
				if (args[idx + 1] != NULL &&
				    strcmp(args[idx + 1], "|"))
				{
					fprintf(stderr, " ");
				}
			}
		}
		
		/* Before anything even gets executed, we replace the special
		 * variables $$ and $? with their respective values. */
		if(strcmp(args[idx], "$$") == 0)
		{
			/* Replace $$ with the last process' process id */
			sprintf(args[idx], "%i", process_id);
		}
		else if (strcmp(args[idx], "$?") == 0)
		{
			/* Replace $? with the last process' exit status */
			sprintf(args[idx], "%i", exit_status);
		}
		
		/* If the current token is the input redirection operatior,
		 * then we load the following token and set it as the input
		 * source.
		 */
		if(strcmp(args[idx], "<") == 0)
		{
			/* Erase the operator token from the token stream */
			args[idx] = NULL;
			
			/* If the user does not provide an input source, notify
			 * them of the error.
			 */
			if (args[idx+1] == NULL)
			{
				fprintf(stderr, "-%s: '<' missing input source\n",
					getprogname()
				);
				return;
			}
			
			inputfile = args[idx + 1];
		}
		else if(strcmp(args[idx], ">") == 0)
		{
			/* Similar to the input redirection operator, for the
			 * output redirection operator we check if an output
			 * source is specified and set that as the outpuf file.
			 */
			
			/* Erase current the operator token */
			args[idx] = NULL;
			
			/* Check if an output file is provided */
			if (args[idx + 1] == NULL)
			{
				fprintf(stderr,
					"-%s: '>' missing output source\n",
					getprogname()
				);
				return;
			}

			outputfile = args[idx + 1];
		}
		else if (strcmp(args[idx], ">>") == 0)
		{
			/* Once again, we must verify the output token for the
			 * append redirection operator.
			 */
			
			args[idx] = NULL;
			
			if (args[idx + 1] == NULL)
			{
				fprintf(stderr,
					"-%s: '>>' missing output source\n",
					getprogname()
				);
				return;
			}
			
			/* Set the IO mode to append */
			mode = "a";
			outputfile = args[idx + 1];
		}
		else if (strcmp(args[idx], "&") == 0)
		{
			/* If the current token is the background process
			 * operator, we reset it to NULL and mark the
			 * background variable to be true.
			 */
			args[idx]  = NULL;
			background = 1;
		}
		else if (strcmp(args[idx],"|") == 0)
		{
			/* If the current token is the pipe operator, we must
			 * verify that the next operator is not NULL and is not
			 * another pipe operator.
			 */
			if (args[idx + 1] == NULL ||
			    strcmp(args[idx + 1], "|") == 0)
			{
				fprintf(stderr,
					"-%s: '|' missing target command\n",
					getprogname()
				);
				return;

			}
			
			/* Reset the token as usual, and mark the beginning of
			 * the next command in the pipe sequence.
			 */
			args[idx]          = NULL;
			command_start[pos] = idx + 1;
			pos++;
		}
		else
		{
			/* For every other token, we simply copy it to
			 * temporary storage.
			 */
			*tmp = args[idx];
			tmp++;
		}
	}
	
	/* If tracing has been enabled, we must add a newline after the end of
	 * the command.
	 */
	if (tracing_enabled)
	{
		fprintf(stderr, "\n");
	}
	
	/* Clear the temporary storage */
	*tmp = NULL;

	/* Fetch the current command from new_args = tmp */
	curr_command = new_args[0];
	
	/* Check the current command for built-in functions*/
	if (strcmp(curr_command, "exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(curr_command, "cd") == 0)
	{
		cd(new_args);
	}
	else if (strcmp(curr_command, "echo") == 0)
	{
		echo(new_args);
	}
	else
	{
		/* If it's not a built-in command, otherwise call the general
		 * purpose command function.
		 */
		command(args, num_commands, command_start, inputfile,
			outputfile, background, mode
		);
	}
	
	/* Now we must reset the arguments used by the commands. */
	while (idx >= 0) {
		args[idx] = NULL;
		idx--;
	}
}


/*	
 *	Counts the number of pipes contained in the provided list of aruments.
 *	
 *	@param		char**		arguments list
 *	
 *	@return		int
 *	
 */
int count_pipes(char** arglist)
{
	int i;
	int count;
	
	for (i = 0, count = 0; arglist[i] != NULL; i++)
	{
		if (strcmp(arglist[i], "|") == 0)
		{
			count++;
		}
	}
	
	return count;
}
