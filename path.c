#include "shell2.h"

char **find_path(char *name, char **envp)
{
	char *search, *path;/*hola*/
	char **array_path;
	int i, buffsize = 32, old_buffsize = 0;

	for (i = 0; envp[i] != NULL; i++)
	{
		search = strtok(envp[i], "=");
		if (_strcmp(name, search) == 0)
		{
			search = strtok(NULL, "\n");
			break;
		}
	}
	array_path = malloc(buffsize * sizeof(char *));
	if (array_path == NULL)
	{
		free(search);
		perror("Could not allocate memory");
		exit(EXIT_FAILURE); /*revisar*/
	}
	path = strtok(search, ":");
	for (i = 0; path; i++)
	{
		array_path[i] = path;
		if (i >= buffsize)
		{
			old_buffsize = buffsize;
			buffsize += 32;
			array_path = _realloc(array_path, old_buffsize * sizeof(char *), buffsize * sizeof(char *));
		}
		path = strtok(NULL, ":");
	}
	array_path[i] = NULL;
	return (array_path);
}

char *path(char **token_array, char *env[])
{
	char **search, *abs_path, *dir;
	int i;

	search = find_path("PATH", env);
	for (i = 0; search[i] != NULL; i++)
	{
		dir = str_concat(search[i], "/");
		abs_path = str_concat(dir, token_array[0]);
		if (access(abs_path, X_OK) == 0)
		{
			free(dir);
			return (abs_path);
		}
		free(dir);
		free(abs_path);
	}
	free(search);
	return (NULL);
}
