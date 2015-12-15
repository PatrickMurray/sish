#include "sish.h"

void eval(char **args)
{
	char *new_args[MAXCOMMANDS];
	char **tmp=new_args;

	char *currentcom;
	char *inputfile=NULL;
	char *outputfile=NULL;
	char background=0;
	char append=0;

	if(*args == NULL)
	{
		return;
	}
	while(*args !=NULL)
	{
		if(strcmp(*args,"<")==0)
		{
			args++;
			if(*args)
			{
				inputfile=*args;
			}
			else
			{
				fprintf(stderr, "Missing name for redirect.\n");
				return;

			}
		}
		else if(strcmp(*args,">")==0)
		{
			args++;
			if(*args)
			{
				outputfile=*args;
			}
			else
			{
				fprintf(stderr, "Missing name for redirect.\n");
				return;
			}

		}
		else if(strcmp(*args, ">>")==0)
		{
			args++;
			if(*args)
			{
				append=1;
				outputfile=*args;
			}
			else
			{
				fprintf(stderr, "Missing name for redirect.\n");
				return;
			}
		}
		else if(strcmp(*args,"&")==0)
		{
			background=1;
		}
		else if(strcmp(*args,"|")==0)
		{
			printf("%s\n","TODO PIPELINE");
		}
		else
		{
			*tmp=(*args);
			tmp++;
		}
		args++;
	}
	tmp=NULL;
	currentcom=new_args[0];
	if(strcmp(currentcom,"exit") == 0)
	{
		exit(EXIT_SUCCESS);
	}
	else if(strcmp(currentcom,"cd") == 0)
	{
		cd(new_args);
	}
	else
	{
		printf("%s\n","TODO COMMAND");
	}
}
