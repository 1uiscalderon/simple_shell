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

/**
 * print_exit_error - Prints an error message when exit built in
 * @arg: Array of arguments from the input(Array_tokens)
 * @name: Name of the shell program
 */

void print_exit_error(char **arg, char *name)
{
	char *str1 = NULL, *str2 = NULL, *str3 = NULL, *str4 = NULL;
	char *str5 = NULL;

	str1 = str_concat(name, ": 1: ");
	str2 = str_concat(str1, arg[0]);
	free(str1);
	str3 = str_concat(str2, ": Illegal number: ");
	free(str2);
	str4 = str_concat(str3, arg[1]);
	free(str3);
	str5 = str_concat(str4, "\n");
	free(str4);
	write(2, str5, _strlen(str5));
	free(str5);
}
