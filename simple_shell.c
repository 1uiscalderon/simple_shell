#include "shell.h"

int main(int argc, char *argv[], char *env[])
{
	int read = 0;
	int is_builtin;
	char *command_line;
	char **token_array;
	char *command_file;
	(void)argc;
	(void)argv;

	signal(SIGINT, signal_handler);
	while (read != -1) /*REVISAR*/
	{
		/*imprimir prompt*/
		write(STDOUT_FILENO, "$ ", 2);
		/*funcion para almacenar linea de argumentos*/
		command_line = read_line(&read);
		if (command_line)
		{
			is_builtin = built_ins(command_line);
			token_array = tokenize(command_line);
			if (token_array)
			{
				/*llamar builtins*/
				/*crear el proceso hijo*/
				command_file = path(token_array, env);
				start_new_process(token_array, env, command_file);
				free(token_array); /*NUEVO CAMBIO*/
													 /*if (command_file)*/
				free(command_file);
			}
			free(command_line);
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
		free(line);				 /*DEBO HACER FREE??*/
		perror("getline"); /*QUE ERROR DEBO ARROJAR?*/
		return (NULL);		 /*DEBO RETORNAR O EXIT?*/
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

char **tokenize(char *line)
{
	int buffsize = 32, old_buffsize = 0, i;
	const char *delimiters = " \n"; /*QUE DELIMITADORES USAR?*/
	char *token;
	char **token_array;

	token_array = malloc(buffsize * sizeof(char *));
	if (token_array == NULL)
	{
		perror("Could not allocate memory");
		return (NULL); /*DEBO RETORNAR O EXIT?*/
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
			if (token_array == NULL) /*QUE PASA SI HAY UN PROBLEMA ?*/
			{
				perror("Could not allocate memory");
				free(token_array); /*VARIFICAR SI SE DEBE HACER ESE FREE*/
				return (NULL);
			}
		}
		token = strtok(NULL, delimiters);
	}
	token_array[i] = NULL;
	return (token_array);
}

int start_new_process(char **arguments, char **env, char *command_file)
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
					free(command_file), perror("execve error");
					exit(EXIT_FAILURE);
				}
			}
			perror("execve error");
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
