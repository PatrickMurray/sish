#include <stdio.h>
#include <stdlib.h>
#include <bsd/stdlib.h>
#include <string.h>
#include <strings.h>

#include "command.h"

#ifndef COMMAND_MAX_LENGTH
#define COMMAND_MAX_LENGTH 65536
#endif


void shell_start();
