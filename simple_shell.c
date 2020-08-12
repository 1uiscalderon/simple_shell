#include "shell.h"

int main(int argc, char *argv[], char *env[])
{
	char *command_line;
	char **token_array;
	(void)argc;
	(void)argv;
	/*loop hasta que reciba el signal de salida*/
	do
	{
		/*imprimir prompt*/
		write(STDOUT_FILENO, "$ ", 2);
		/*funcaion para recibir argumentos y almacenar linea de argumentos*/
		command_line = read_line(); /*REVISAR*/
		/*tokenizar*/
		token_array = tokenize(command_line);
		/*crear el proceso hijo*/
		start_new_process(token_array, env);
		/*liberar memoria*/
		free(command_line);
	} while (1); /*REVISAR*/
	return (0);
}
char *read_line(void)
{
	int rd;
	ssize_t size = 0;
	char *line = NULL;
	rd = getline(&line, &size, stdin);
	/*if (rd == -1)
	{
		perror("getline"); 
		exit(EXIT_FAILURE);
	}*/
	return (line);
}

char **tokenize(char *line)
{
	int buffsize = 32, old_buffsize = 0, i; /*posicion del array*/
	char *token;
	const char *delimiters = " "; /*solo por espacios ahora*/
	char **token_array;

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
		/*if (i >= buffsize)
		{
			old_buffsize = buffsize;
			buffsize += 32;
			token_array = _realloc(token_array, old_buffsize * sizeof(char *), buffsize * sizeof(char *));
		if (token_array == NULL)
		{
			free(line); /*REVISAR SI NECESITAMOS LIBERAR TOKEN_ARRAY
		perror("_realloc error");
		exit(EXIT_FAILURE); revisar
	}
	*/
		token = strtok(NULL, delimiters);
	}
	token_array[i] = NULL;
	return (token_array);
}

int start_new_process(char **arguments, char **env)
{
	pid_t pid;
	int status = 0; /*revisar*/

	pid = fork();

	if (pid == -1)
	{
		/*error in fork*/
		perror("fork error");
		exit(EXIT_FAILURE);
	}

	if (pid == 0)
	{
		/*child process*/
		if (execve(arguments[0], arguments, env) == -1)
		{
			perror("execve error");
			exit(EXIT_FAILURE);
		}
	}

	else
	{
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