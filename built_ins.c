#include "shell.h"

int built_ins(char **arguments, char *command_line, char *env[])
{
	int i;
	if (_strcmp("exit", arguments[0]) == 0)
	{
		free(command_line);
		free(arguments);
		exit(EXIT_SUCCESS);
	}
	if (_strcmp("env", arguments[0]) == 0)
	{
		for (i = 0; env[i] != NULL; i++)
		{
			write(STDOUT_FILENO, env[i], _strlen(env[i]));
		}
		write(STDOUT_FILENO, "\n", 1);
		return (1);
	}
	return (0);
}
