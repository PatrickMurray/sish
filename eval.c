#include "sish.h" 
void eval(char** args, int pipes)
{
	int    idx;
	int    pos=1;
	char*  new_args[MAXCOMMANDS];
	char** tmp;
	char*  currentcom;
	char*  inputfile;
	char*  outputfile;
	char   background;
	char*  mode;
	int    command_start[10];

	
	tmp          = new_args;
	inputfile    = NULL;
	outputfile   = NULL;
	background   = 0;
	mode         = "w";
	num_commands = pipes+1;
	command_start[0]=0;

	if (*args == NULL)
	{
		return;
	}
	
	if (tracing_enabled)
	{
		fprintf(stderr, "+ ");
	}

	idx = 0;
	while (args[idx] != NULL)
	{
		if (tracing_enabled)
		{
			if (strcmp(args[idx], "|") == 0)
			{
				fprintf(stderr, "\n+ ");
			}
			else
			{
				fprintf(stderr, "%s", args[idx]);
				if (args[idx + 1] != NULL &&
				    strcmp(args[idx + 1], "|"))
				{
					fprintf(stderr, " ");
				}
			}
		}
		
		if(strcmp(args[idx], "$$") == 0)
		{
			/* Replace the process id */
			sprintf(args[idx], "%i", process_id);
		}
		else if (strcmp(args[idx], "$?") == 0)
		{
			/* Replace the exit status */
			sprintf(args[idx], "%i", exit_status);
		}
		if(strcmp(args[idx], "<") == 0)
		{
			args[idx]=NULL;
			if(args[idx+1])
			{
				inputfile =args[idx+1];
			}
			else
			{
				fprintf(stderr, "Missing name for redirect.\n");
				return;
			}
		}
		else if(strcmp(args[idx], ">") == 0)
		{
			args[idx]=NULL;
			if(args[idx+1])
			{
				outputfile = args[idx+1];
			}
			else
			{
				fprintf(stderr, "Missing name for redirect.\n");
				return;
			}

		}
		else if (strcmp(args[idx], ">>") == 0)
		{
			args[idx]=NULL;
			if(args[idx+1])
			{
				mode = "a";
				outputfile = args[idx+1];
			}
			else
			{
				fprintf(stderr, "Missing name for redirect.\n");
				return;
			}
		}
		else if (strcmp(args[idx], "&") == 0)
		{
			args[idx]=NULL;
			background = 1;
		}
		else if (strcmp(args[idx],"|") == 0)
		{
			if(args[idx+1])
			{
				args[idx]=NULL;
				command_start[pos]=idx+1;
				pos++;
			}
			else
			{
				fprintf(stderr, "Missing process name for pipe.\n");
				return;

			}
		}
		else
		{
			*tmp = args[idx];
			tmp++;
		}

		idx++;
	}
	
	if (tracing_enabled)
	{
		fprintf(stderr, "\n");
	}

	*tmp=NULL;
	currentcom = new_args[0];
	
	if(strcmp(currentcom,"exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if(strcmp(currentcom, "cd") == 0)
	{
		cd(new_args);
	}
	else if(strcmp(currentcom, "echo") == 0)
	{
		echo(new_args);
	}
	else
	{
		command(args,num_commands,command_start,inputfile,outputfile,background,mode);
	}
	
	while (idx >= 0) {
		args[idx] = NULL;
		idx--;
	}
}
