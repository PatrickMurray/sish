/*
 * LEX SPECIFICATION
 *
 */

%option noyywrap
%option noinput
%option nounput

%{

#undef _POSIX_SOURCE
#define _POSIX_SOURCE
#define YY_PROTO(proto) proto
#define YY_DECL char **yylex YY_PROTO(( void ))

#undef YY_INPUT
#define YY_INPUT(b,r,s) readInputForLexer(b,&r,s)

#include "sish.h"

int comcount=0;
char* inputtext;
extern int readInputForLexer(char* buffer,int *numBytesRead,int maxBytesToRead);
%}

WORDS	[a-zA-Z0-9\/\.\-\=\^$\\?]+
OPS		[><|&]|>>

%%
	comcount=0;
	_args[0]=NULL;

{WORDS}|{OPS} {
		if(comcount < maxargs-1)
		{
			 _args[comcount++] = (char *)strdup(yytext);
			 _args[comcount] = NULL;
		}
	}

\n return _args;


[ \t]+

. return NULL;

%%

char** parse(char* line)
{	
	if((inputtext=malloc(strlen(line)+strlen("\n")+1)) != NULL)
	{
		inputtext[0]='\0';
		strcat(inputtext,line);
		strcat(inputtext,"\n");
	} 
	else 
	{
		fprintf(stderr,"malloc failed!\n");
		exit(EXIT_FAILURE);
	}
	return (char **)yylex();
}

int readInputForLexer( char *buffer, int *numBytesRead, int maxBytesToRead ) {
    int numBytesToRead = maxBytesToRead;
    int bytesRemaining = strlen(inputtext);
    int i;

    if(numBytesToRead > bytesRemaining )
	{ 
		numBytesToRead = bytesRemaining; 
	}
    for(i = 0;i<numBytesToRead;i++)
	{
        buffer[i] = inputtext[i];
    }
    *numBytesRead=numBytesToRead;
    return 0;
}
