#include "shell.h"

char **find_path(char **envp)
{
	char **array_path = NULL;
	char **path = NULL;
	int i;

	for (i = 0; envp[i] != NULL; i++)
	{
		path = strtok_arr(envp[i], "="); /*DYNAMIC MEMORY ALLOC*/
		if (_strcmp("PATH", path[0]) == 0)
		{
			array_path = strtok_arr(path[1], ":"); /*DYNAMIC MEMORY ALLOC*/
			free_pointer_array(path);
			return (array_path);
		}
		free_pointer_array(path);
	}
	return (NULL);
}

char *path(char **token_array, char *envp[])
{
	char **dir_array = NULL, *dir = NULL, *possible_file = NULL;
	int i;
	dir_array = find_path(envp);
	if (dir_array == NULL)
		return (NULL);
	for (i = 0; dir_array[i] != NULL; i++)
	{
		dir = str_concat(dir_array[i], "/");						 /*DYNAMIC MEMORY ALLOC*/
		possible_file = str_concat(dir, token_array[0]); /*DYNAMIC MEMORY ALLOC*/
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
