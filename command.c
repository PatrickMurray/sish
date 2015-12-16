#include "sish.h"

void command(char** command, char* in, char* out, char bg, char* mode)
{
	int   status;
	pid_t pid;
	pid_t reap_pid;
	
	if((pid = fork()) > 0)
	{
		if(!bg)
		{
			do
			{
				reap_pid = wait(&status);
				if(reap_pid != pid)
				{
					printf("%d: background process terminated\n", reap_pid);
				}

			}
			while(reap_pid !=pid);
		}
	}
	else if(pid == 0) /* CHILD */
	{
		if(in != NULL)
		{
			if(freopen(in, "r", stdin) == NULL)
			{  
				fprintf(stderr, "Error opening input stream\n"); 
			}
		}
		if(out != NULL)
		{
			if(freopen(out, mode, stdout) == NULL)
			{  
				fprintf(stderr, "Error opening input stream\n"); 
			}
		}
		execvp(command[0], command);
	}
	else
	{
		fprintf(stderr, "Error forking a child process\n");
	}


}
