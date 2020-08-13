#include "shell.h"

int main(int argc, char *argv[], char *env[])
{
	int read = 0;
	char *command_line;
	char **token_array;
	(void)argc;
	(void)argv;

	signal(SIGINT, signal_handler); /*SIGINT == ^C*/
	while (read != -1)
	{
		/*imprimir prompt*/
		write(STDOUT_FILENO, "$ ", 2);
		/*funcaion para recibir argumentos y almacenar linea de argumentos*/
		command_line = read_line(&read); /*REVISAR*/
		/*tokenizar*/
		if (command_line)
		{
			token_array = tokenize(command_line);
			if (token_array)
			{
				/*crear el proceso hijo*/
				start_new_process(token_array, env);
				/*liberar token*/
				/** OJJJOOOOOOO*/
			}
			free(command_line);
			free(token_array);
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
		free(line);
		perror("getline");
		return (NULL);
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
	int buffsize = 32, old_buffsize = 0, i; /*posicion del array*/
	const char *delimiters = " \n";					/*solo por espacios ahora*/
	char *token;
	char **token_array;

	token_array = malloc(buffsize * sizeof(char *));
	if (token_array == NULL)
	{
		perror("Could not allocate memory");
		return (NULL); /*revisar*/
	}
	token = strtok(line, delimiters); /* Solo dividir por espacios" */
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
				return (NULL); /*revisar*/
			}
		}
		token = strtok(NULL, delimiters);
	}
	token_array[i] = NULL;
	return (token_array);
}

int start_new_process(char **arguments, char **env)
{
	pid_t pid;
	int status;
	char *command_file;

	pid = fork();
	switch (pid)
	{
	case -1:
		/*error in fork*/
		perror("fork error");
		exit(EXIT_FAILURE);
	case 0:
		/*child process*/
		if (execve(arguments[0], arguments, env) == -1)
		{
			command_file = path(arguments, env);
			if (execve(command_file, arguments, env) == -1)
			{
				perror("execve error");
				return (0);
			}
		}
	default:
		/*parent process*/
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
