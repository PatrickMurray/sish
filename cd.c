#include "sish.h"

void cd(char **args)
{
	char* dir;
	struct passwd *user;

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
	
	if(chdir(dir) < 0)
	{
		fprintf(stderr,"cd: %s: No such file or directory\n", dir);
		//args[1]=NULL;
	}
}
