#include "shell.h"

int main(int argc, char *argv[], char *env[])
{
	int token_counter;
	char *command_line;
	char **token_array;
	char *token;
	(void)argc;
	(void)argv;

	do
	{
		/*imprimir prompt*/
		write(STDOUT_FILENO, "$ ", 2);
		/*funcaion para recibir argumentos y almacenar linea de argumentos*/
		command_line = read_line(); /*REVISAR*/
		/*tokenizar*/
		token_array = tokenize(command_line, token_array, token);
		/*crear el proceso hijo*/
		start_new_process(token_array, env);
		/*liberar token*/

	} while (1); /*REVISAR*/
	free(command_line);
	free(token_array);
	return (0);
}
char *read_line(void)
{
	int rd;
	ssize_t size = 0;
	char *line = NULL;
	rd = getline(&line, &size, stdin);
	if (rd == -1)
	{
		perror("getline");
		exit(EXIT_FAILURE);
	}
	return (line);
}

char **tokenize(char *line, char **token_array, char *token)
{
	int buffsize = 32, old_buffsize = 0, i; /*posicion del array*/
	const char *delimiters = " \n";					/*solo por espacios ahora*/

	token_array = malloc(buffsize * sizeof(char *));
	if (token_array == NULL)
	{
		perror("Could not allocate memory");
		exit(EXIT_FAILURE); /*revisar*/
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
			perror("execve error");
			exit(EXIT_FAILURE);
		}
	default:
		/*parent process*/
		do
		{
			if (waitpid(pid, &status, WUNTRACED) == -1)
			{
				perror("waitpid error");
				exit(EXIT_FAILURE);
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}
