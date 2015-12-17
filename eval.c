#include "sish.h" 
void eval(char** args, int pipes)
{
	int i=0;
	int pos=1;
	char*  new_args[MAXCOMMANDS];
	char** tmp;
	char*  currentcom;
	char*  inputfile;
	char*  outputfile;
	char   background;
	char*  mode;
	char*  buffer[BUFFER_SIZE];
	int	command_start[10];

	
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
	while (args[i] != NULL)
	{
				
		if(strcmp(args[i], "$$") == 0)
		{
			/* Replace the process id */
			bzero(buffer, BUFFER_SIZE);
			sprintf(*args, "%i", process_id);
		}
		else if (strcmp(args[i], "$?") == 0)
		{
			/* Replace the exit status */
			bzero(buffer, BUFFER_SIZE);
			sprintf(*args, "%i", exit_status);
		}
		if(strcmp(args[i], "<") == 0)
		{
			args[i]=NULL;
			if(args[i+1])
			{
				inputfile =args[i+1];
			}
			else
			{
				fprintf(stderr, "Missing name for redirect.\n");
				return;
			}
		}
		else if(strcmp(args[i], ">") == 0)
		{
			args[i]=NULL;
			if(args[i+1])
			{
				outputfile = args[i+1];
			}
			else
			{
				fprintf(stderr, "Missing name for redirect.\n");
				return;
			}

		}
		else if (strcmp(args[i], ">>") == 0)
		{
			args[i]=NULL;
			if(args[i+1])
			{
				mode = "a";
				outputfile = args[i+1];
			}
			else
			{
				fprintf(stderr, "Missing name for redirect.\n");
				return;
			}
		}
		else if (strcmp(args[i], "&") == 0)
		{
			args[i]=NULL;
			background = 1;
		}
		else if (strcmp(args[i],"|") == 0)
		{
			args[i]=NULL;
			command_start[pos]=i+1;
			pos++;
		}
		else
		{
			*tmp = args[i];
			tmp++;
		}
		i++;
	}
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
}
