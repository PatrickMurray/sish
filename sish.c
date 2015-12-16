#include "sish.h"


void sigintHandler(int sig_num)
{
	printf("\n");
	fflush(stdout);
	
	if(signal(SIGINT, sigintHandler) == SIG_ERR)
	{
		perror("sish: signal() failed.");
		exit(EXIT_FAILURE);
	}
	
	printf("sish_1.0$ ");
}


int main(int argc, char** argv) 
{
	char   flag;	
	char*  input;
	char** arglist;
	char*  shell_prompt;
	char*  exec_path;
	char   buffer[PATH_MAX + 1];
	
	shell_prompt = "sish_1.0$ ";
	

	exit_status = 0;
	process_id = getpid();
	

	setprogname(argv[0]);
	
	if ((exec_path = realpath(argv[0], buffer)) == NULL) {
		fprintf(stderr, "%s: unable to resolve path: %s\n",
			getprogname(), strerror(errno)
		);
		exit(EXIT_FAILURE);
	}

	if (setenv("SHELL", exec_path, 1) == -1) {
		fprintf(stderr, "%s: unable to set SHELL: %s\n", getprogname(),
			strerror(errno)
		);
		exit(EXIT_FAILURE);
	}

	/* Override getopt() error messages */
	opterr = 0;
	while ((flag = getopt(argc, argv, ":xc:")) >= 0) 
	{
		switch (flag) {
			case 'x':
				tracing_enabled = 1;
				break;
			case 'c':
				arguments_command = optarg;
				break;
			case ':':
				fprintf(stderr,
					"%s: -%c requires an argument\n",
					getprogname(), optopt
				);
				exit(EXIT_FAILURE);
			case '?':
			default:
				fprintf(stderr, "%s: unknown flag -%c\n",
					getprogname(), optopt
				);
				exit(EXIT_FAILURE);
		}
	}
	
	if(arguments_command == NULL)
	{
		if(signal(SIGINT, sigintHandler) == SIG_ERR)
		{
			perror("sish: signal() failed.");
			exit(EXIT_FAILURE);
		}

		while(1)
		{ 
			input = readline(shell_prompt);
			if(!input)
			{
				break;
			}
			if((strlen(input) == 0))
			{
				continue;
			}
			arglist=(char**)parse(input);
			if(arglist != NULL)
			{
				eval(arglist);
			}
		} 
	}
	else 
	{
		arglist = parse(arguments_command);
		if (arglist != NULL)
		{
			eval(arglist);
		}
	}

	return EXIT_SUCCESS;
}
