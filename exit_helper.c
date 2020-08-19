#include "shell.h"
/**
 * print_env_error - Prints an error message when printing env
 * combined with another word
 * @arg: Array of arguments from the input(Array_tokens)
 */

void print_env_error(char **arg)
{
	char *str1 = NULL, *str2 = NULL, *str3 = NULL;

	str1 = str_concat(arg[0], ": ");
	str2 = str_concat(str1, arg[1]);
	free(str1);
	str3 = str_concat(str2, ": No such file or directory\n");
	free(str2);
	write(2, str3, _strlen(str3));
	free(str3);
}

/**
 * print_error - Prints an error message when execve cant execute a line
 * @arg: Array of arguments from the input(Array_tokens)
 * @name: Name of the shell program
 */

void print_error(char **arg, char *name)
{
char *str1 = NULL, *str2 = NULL, *str3 = NULL;

	str1 = str_concat(name, ": 1: ");
	str2 = str_concat(str1, arg[0]);
	free(str1);
	str3 = str_concat(str2, ": not found\n");
	free(str2);
	write(2, str3, _strlen(str3));
	free(str3);
}
