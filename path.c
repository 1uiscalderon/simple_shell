#include "shell.h"

char **find_path(char *name, char **envp)
{
	char *search;
	char **array_path;
	char *path;
	int i = 0;

	for (i = 0; envp[i] != NULL; i++)
	{
		search = strtok(envp[i], "=");
		if (strcmp(name, search) == 0)
		{
			search = strtok(NULL, "\n");
			break;
		}
		else
			free(search);
	}
	array_path = malloc(32 * sizeof(char *));
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
		path = strtok(NULL, ":");
	}
	array_path[i] = NULL;
	return (array_path);
}

char *path(**token_array, char *env[])
{
	char **search, **abs_path, *dir;
	(void)token_array;
	int i;

	search = find_path("PATH", env);
	for (i = 0; search[i] != NULL; i++)
	{
		dir = str_concat(search[i], "/");
		abs_path = str_concat(dir, token_array[0]);
		if (access(abs_path, X_OK) == 0)
		{
			free(array_path);
			free(dir);
			return (abs_path);
		}
		free(dir);
		free(abs_path);
	}
	free(search);
	return (NULL);
}
