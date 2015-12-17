#include "sish.h"


int count_commands(char** arglist) {
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


void command(char** args,int commands,int start[], char* in, char* out, char bg, char* mode)
{
	int i=0;
	int pid;
	int status;
	int place;
	int j=0;
	int q=0;
	
	int pipes=commands-1;
	int pipefds[2*pipes];
	start[0]=0;
	
	exit_status = 0;
	
	for(i=0;i<pipes;i++)
	{
		if(pipe(pipefds+i*2) < 0)
		{
			perror("Couldn't Pipe");
			exit(EXIT_FAILURE);
		}
	}
	
	for(i=0;i<commands;++i)
	{
		 place = start[i];
		 if((pid = fork())==0)
		 {
			/* if not last command */
			if(i < pipes)
			{
				if(dup2(pipefds[j+1],1) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			if(j!=0)
			{
				if(dup2(pipefds[j-2], 0) < 0)
				{
					perror("dup2");
					exit(EXIT_FAILURE);
				}
			}
			for(q = 0; q < 2*pipes; q++)
			{
				close(pipefds[q]);
			}
			if(execvp(args[place],args+place)<0)
			{
				perror(*args);
				exit(EXIT_FAILURE);
			}
		}
		else if(pid < 0)
		{
			perror("error");
			exit(EXIT_FAILURE);
		}
		j+=2;
	}

	for(i=0;i<2*pipes;i++)
	{
		close(pipefds[i]);
	}
	for(i=0;i<pipes+1;i++)
	{
		wait(&status);
	}
}
