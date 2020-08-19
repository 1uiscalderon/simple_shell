#include "shell.h"

/**
 * find_path - Returns an array of directories in the PATH.
 * @envp: Enviroment, double pointer where PATH is located
 * Return: Array of strings
 */
char **find_path(char **envp)
{
	char **array_path = NULL;
	char **path = NULL;
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		path = strtok_arr(envp[i], "=");
		if (_strcmp("PATH", path[0]) == 0)
		{
			array_path = strtok_arr(path[1], ":");
			free_pointer_array(path);
			return (array_path);
		}
		free_pointer_array(path);
	}
	return (NULL);
}

/**
 * path - Returns the path to be executed with execve.
 * @token_array: Double pointer with the input
 * @envp: Enviroment
 * Return: path to be executed if found.
 */

char *path(char **token_array, char *envp[])
{
	char **dir_array = NULL, *dir = NULL, *possible_file = NULL;
	int i;

	if (token_array[0] == NULL)
	{
		exit(EXIT_FAILURE);
	}
	dir_array = find_path(envp);
	if (dir_array == NULL)
		return (NULL);
	for (i = 0; dir_array[i] != NULL; i++)
	{
		dir = str_concat(dir_array[i], "/");
		possible_file = str_concat(dir, token_array[0]);
		if (access(possible_file, X_OK) == 0)
		{
			free_pointer_array(dir_array);
			free(dir);
			return (possible_file);
		}
		free(dir);
		free(possible_file);
	}
	free_pointer_array(dir_array);
	return (NULL);
}
