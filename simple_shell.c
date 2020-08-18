#include "shell.h"

int main(int argc, char *argv[], char *env[])
{
	int read = 0, i = 0;
	int is_builtin = 0;
	char *command_line = NULL;
	char **token_array = NULL;
	char *command_file = NULL;
	(void)argc;
	char *p_name = argv[0];

	signal(SIGINT, signal_handler);
	while (read != -1) /*REVISAR*/
	{
		write(STDOUT_FILENO, "$ ", 2);
		command_line = read_line(&read);
		if (_strcmp(command_line, "\n") == 0)
		{
			free(command_line);
			command_line = NULL;
			continue;
		}
		if (command_line)
		{
			token_array = strtok_arr(command_line, " \n");
			free(command_line);
			if (token_array)
			{
				is_builtin = built_ins(token_array, env);
				if (is_builtin == 0)
				{
					command_file = path(token_array, env);
					start_new_process(token_array, env, command_file, p_name);
					free(command_file);
				}
				free_pointer_array(token_array);
			}
		}
	}
	return (0);
}

char *read_line(int *rd)
{
	ssize_t size = 0;
	char *line = NULL;
	*rd = getline(&line, &size, stdin);
	if (*rd == -1)
	{
		free(line); /*DEBO HACER FREE??*/
		line = NULL;
		/*perror("getline");*/	/*QUE ERROR DEBO ARROJAR?*/
		exit(EXIT_SUCCESS); /*DEBO RETORNAR O EXIT?*/
	}
	return (line);

	/**
	char *line = malloc(1024);
	while (1)
	{
		*rd = read(STDIN_FILENO, line++, 1024);
		if (*rd == -1)
		{
			*line = '\0';
			return (line);
		}
	}
	*/
}

/**char **tokenize(char *line)
{
	int buffsize = 32, old_buffsize = 0, i;
	const char *delimiters = " \n";
	char *token = NULL;
	char **token_array = NULL;

	token_array = malloc(buffsize * sizeof(char *));
	if (token_array == NULL)
	{
		perror("Could not allocate memory");
		return (NULL); 
	}
	token = strtok(line, delimiters);
	for (i = 0; token; i++)
	{
		token_array[i] = token;
		if (i >= buffsize)
		{
			old_buffsize = buffsize;
			buffsize += 32;
			token_array = _realloc(token_array, old_buffsize * sizeof(char *), buffsize * sizeof(char *));
			if (token_array == NULL) 
			{
				perror("Could not allocate memory");
				free(token_array); 
				return (NULL);
			}
		}
		token = strtok(NULL, delimiters);
	}
	token_array[i] = NULL;
	return (token_array);
}
*/

int start_new_process(char **arguments, char **env, char *command_file, char *p_name)
{
	pid_t pid;
	int status;

	pid = fork();
	switch (pid)
	{
	case -1:
		perror("fork error");
		return (0);
	case 0:
		if (execve(arguments[0], arguments, env) == -1)
		{
			if (command_file)
			{
				if (execve(command_file, arguments, env) == -1)
				{
					free(command_file), free_pointer_array(arguments);
					print_error(arguments, p_name);
					exit(EXIT_FAILURE);
				}
			}
			/*perror(NULL);*/
			print_error(arguments, p_name);
			free_pointer_array(arguments);
			exit(EXIT_FAILURE);
		}
	default:
		do
		{
			if (waitpid(pid, &status, WUNTRACED) == -1)
			{
				perror("waitpid error");
				return (0);
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}
