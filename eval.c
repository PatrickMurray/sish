#include "sish.h" 
void eval(char** args,int pipes)
{
	int i=0;
	int j=0;
	int k=0;
	int q=0;
	int pid;
	int status;
	int place;
	int s=1;
/*
	char* inputfile=NULL;
	char* outputfile=NULL;
	char  background=0;
	char* mode="w";
*/
	int commands=pipes+1;
	int pipefds[2*pipes];
	int commandStarts[10];
	commandStarts[0] = 0;

	if(*args == NULL)
	{
		return;
	}
	for(i=0;i<pipes;i++)
	{
		if(pipe(pipefds+i*2) < 0)
		{
			perror("Couldn't Pipe");
			exit(EXIT_FAILURE);
		}
	}
	/* INTERNALS */
	while(args[k] != NULL)
	{
		if(!strcmp(args[k], "|"))
		{
			args[k] = NULL;
			commandStarts[s] = k+1;
			s++;
		}
		k++;
	}

	/** INTERNAL */


	/** PIPES **/
	for(i=0;i<commands;++i)
	{
		 place = commandStarts[i];
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
	/** REDIRECTIONS **/

	for(i=0;i<2*pipes;i++)
	{
		close(pipefds[i]);
	}
	for(i=0;i<pipes+1;i++)
	{
         wait(&status);
	}

/*
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
*/
}
