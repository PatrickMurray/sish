#include "sish.h"


char* shell_prompt      = "sish$ ";
int   tracing_enabled   = 0;
char* arguments_command = NULL;
int   process_id        = 0;
int   exit_status       = 0;


/*	
 *	An implementation of a simple shell with background processes,
 *	redirection, and pipes.
 *	
 *	@param		int
 *	@param		char**
 *	
 *	@return		int
 *	
 */
int main(int argc, char** argv) 
{
	char*  input;
	char** arglist;
	int    num_pipes;
	
	setprogname(argv[0]);
	set_shell(argv[0]);
	parse_arguments(argc, argv);
	
	/* Establish the initial values of $? to be the shell PID */
	process_id = getpid();
	
	/* If the user provides a command in the arguments */
	if (arguments_command != NULL)
	{
		arglist = parse(arguments_command);
		
		if (arglist != NULL)
		{
			num_pipes = count_pipes(arglist);
			eval(arglist, num_pipes);
		}

		free(arglist);
	}
	else
	{
		/* Otherwise, set up the shell prompt */
		
		if(signal(SIGINT, sigint_handler) == SIG_ERR)
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
			
			if(strlen(input) == 0)
			{
				continue;
			}
			
			/* Why not add shell history :) */
			add_history(input);
			
			arglist = parse(input);

			if(arglist != NULL)
			{
				num_pipes = count_pipes(arglist);
				eval(arglist, num_pipes);
			}

			free(arglist);
		}
	}
	
	return EXIT_SUCCESS;
}


/*	
 *	Set's the SHELL environment variable.
 *	
 *	@param		char*		the program's executable name
 *	
 *	@return		void
 *	
 */
void set_shell(char* program_name)
{
	char* exec_path;
	char  buffer[PATH_MAX + 1];
	
	if ((exec_path = realpath(program_name, buffer)) == NULL) {
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
}


/*	
 *	Parses arguments in argv and establishes the tracing_enabled and
 *	arguments_command global variable.
 *	
 *	@param		int		argc
 *	@param		char**		argv
 *	
 *	@return		void
 *	
 */
void parse_arguments(int argc, char** argv)
{
	char flag;
	
	/* Override getopt() error messages, we will use our own */
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
}


/*	
 *	Signal handler to ignore interrupts in the shell prompt.
 *	
 *	@param		int		signal number
 *	
 *	@return		void
 *	
 */
void sigint_handler(int sig_num)
{
	printf("\n");
	fflush(stdout);
	
	if(signal(SIGINT, sigint_handler) == SIG_ERR)
	{
		perror("sish: signal() failed.");
		exit(EXIT_FAILURE);
	}
	
	printf("%s", shell_prompt);
}
