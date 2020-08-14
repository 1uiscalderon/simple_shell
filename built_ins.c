#include "shell.h"

int built_ins(char *command_line)
{

	if (_strcmp("exit\n", command_line) == 0)
	{
		free(command_line);
		exit(EXIT_SUCCESS);
	}
	/*if (_strcmp("env", arguments[0]));
		if (_strcmp("cd", arguments[0]));*/
}
