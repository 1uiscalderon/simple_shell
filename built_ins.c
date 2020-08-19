#include "shell.h"

/**
 * built_ins - Check if the commands are builtin
 * @arguments: Tokenized input
 * @env: Array of enviroment variables
 * Return: 1 on success
 */

int built_ins(char **arguments, char *env[])
{
	int i;

	if (_strcmp("exit", arguments[0]) == 0)
	{

		if (arguments[1] != NULL)
		{
			free_pointer_array(arguments);/*add*/
			exit(-1);
		}
		free_pointer_array(arguments);
		exit(EXIT_SUCCESS);
	}
	if (_strcmp("env", arguments[0]) == 0)
	{
		if (arguments[1] == NULL)
		{
			for (i = 0; env[i] != NULL; i++)
			{
				write(STDOUT_FILENO, env[i], _strlen(env[i]));
				if (env[i + 1] != NULL)
				write(STDOUT_FILENO, "\n", 1);
			}
			write(STDOUT_FILENO, "\n", 1);
		}
		else
		print_env_error(arguments);
		return (1);
	}
	return (0);
}
