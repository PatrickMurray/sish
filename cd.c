#include "sish.h"

void cd(char **args)
{
	char* dir;
	struct passwd *user;
	int i;
	
	dir = args[1];
	if(dir == NULL)
	{
		if((user = getpwuid(getuid())) == NULL)
		{
			perror("getpwuid() failed.");
			return;
		}
		dir = user->pw_dir;
	}

	if(chdir(dir) == -1)
	{
		fprintf(stderr, "cd  %s: %s\n", dir, strerror(errno));
	}
	
	dir = NULL;
}
