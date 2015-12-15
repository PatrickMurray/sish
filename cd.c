#include "sish.h"

void cd(char **args)
{
	struct passwd *home_dir = NULL;
	if(args[1] == NULL)
	{
		if((home_dir=getpwuid(getuid())) == NULL)
		{
			perror("getpwuid() failed.");
			return;
		}
	}
	else
	{
		if(chdir(args[1]) < 0)
		{
			fprintf(stderr,"cd: %s: No such file or directory\n", args[1]);
			args[1]=NULL;
		}
	}
}
