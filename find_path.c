#include "shell.h"

char **find_path(char **envp)
{
	char *path_var = NULL, *path = NULL;
	char **array_path = NULL;
	int i, buffsize = 32, old_buffsize = 0;

	for (i = 0; envp[i] != NULL; i++)
	{
		path_var = strtok(envp[i], "=");
		if (_strcmp("PATH", path_var) == 0) /*ELIMINE VARIABLE Y LA CONVERTI EN STRING LITERAL*/
		{
			path_var = strtok(NULL, "\n");
			break; /* QUE PASA SI NO ENCUENTRA PATH??*/
		}
	}
	array_path = malloc(buffsize * sizeof(char *));
	if (array_path == NULL)
	{
		free(path_var);
		perror("Could not allocate memory");
		return (0); /*revisar*/
	}
	path = strtok(path_var, ":");
	for (i = 0; path; i++)
	{
		array_path[i] = path;
		if (i >= buffsize)
		{
			old_buffsize = buffsize;
			buffsize += 32;
			array_path = _realloc(array_path, old_buffsize * sizeof(char *), buffsize * sizeof(char *));
			if (array_path == NULL)
			{
				perror("Could not allocate memory");
				free(array_path); /*ES NECESARIO LIBERAR?*/
				return (NULL);
			}
		}
		path = strtok(NULL, ":");
	}
	array_path[i] = NULL;
	return (array_path);
}

char *path(char **token_array, char *env[])
{
	char **dir_array = NULL, *dir = NULL, *possible_file = NULL;
	int i;

	dir_array = find_path(env); /*Elimine un argumento*/
	for (i = 0; dir_array[i] != NULL; i++)
	{
		dir = str_concat(dir_array[i], "/");
		possible_file = str_concat(dir, token_array[0]);
		if (access(possible_file, X_OK) == 0)
		{
			free(dir_array);
			free(dir);
			return (possible_file);
		}
		free(dir);
		free(possible_file);
	}
	free(dir_array);
	return (NULL);
}
