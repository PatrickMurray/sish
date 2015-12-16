#include "sish.h"

void command(char** command, char* in, char* out, char bg, char* mode)
{
	int   i;
	pid_t pid;
	pid_t reap_pid;
	
	exit_status = 0;

	if (tracing_enabled)
	{
		printf("+ ");
		for (i = 0; command[i]; i++) {
			printf("%s", command[i]);

			if (command[i+1] != NULL)
			{
				printf(" ");
			}
		}
		printf("\n");
	}
	
	if((pid = process_id = fork()) > 0)
	{
		if(!bg)
		{
			printf("[%i]", process_id);

			do
			{
				reap_pid = wait(&exit_status);
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
