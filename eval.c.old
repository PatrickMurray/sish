#include "sish.h" 
void eval(char** args)
{
	int i;
	char*  new_args[MAXCOMMANDS];
	char** tmp;
	char*  currentcom;
	char*  inputfile;
	char*  outputfile;
	char   background;
	char*  mode;
	char*  buffer[BUFFER_SIZE];
	
	tmp          = new_args;
	inputfile    = NULL;
	outputfile   = NULL;
	background   = 0;
	mode         = "w";
	num_commands = 1;
	i=0;

	if (*args == NULL)
	{
		return;
	}
	while(args[i] !=NULL)
	{
		if(strcmp(args[i], "|") == 0)
		{
			num_commands++;
		}
		i++;
	}
	printf("%d\n",num_commands);

	while (*args != NULL)
	{
				
		if (strcmp(*args, "$$") == 0)
		{
			/* Replace the process id */
			bzero(buffer, BUFFER_SIZE);
			sprintf(*args, "%i", process_id);
		}
		else if (strcmp(*args, "$?") == 0)
		{
			/* Replace the exit status */
			bzero(buffer, BUFFER_SIZE);
			sprintf(*args, "%i", exit_status);
		}
		
		if (strcmp(*args, "<") == 0)
		{
			args++;

			if (*args)
			{
				inputfile = *args;
			}
			else
			{
				fprintf(stderr, "Missing name for redirect.\n");
				return;
			}
		}
		else if (strcmp(*args, ">") == 0)
		{
			args++;

			if (*args)
			{
				outputfile = *args;
			}
			else
			{
				fprintf(stderr, "Missing name for redirect.\n");
				return;
			}

		}
		else if (strcmp(*args, ">>") == 0)
		{
			args++;

			if (*args)
			{
				mode = "a";
				outputfile = *args;
			}
			else
			{
				fprintf(stderr, "Missing name for redirect.\n");
				return;
			}
		}
		else if (strcmp(*args, "&") == 0)
		{
			background = 1;
		}
		else if (strcmp(*args,"|") == 0)
		{
			printf("%s\n","TODO PIPELINE");
		}
		else
		{
			*tmp = (*args);
			tmp++;
		}

		args++;
	}

	*tmp = NULL;
	currentcom = new_args[0];
	
	if (strcmp(currentcom,"exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if (strcmp(currentcom, "cd") == 0)
	{
		cd(new_args);
	}
	else if (strcmp(currentcom, "echo") == 0)
	{
		echo(new_args);
	}
	else
	{
		command(new_args, inputfile, outputfile, background, mode);
	}
}
