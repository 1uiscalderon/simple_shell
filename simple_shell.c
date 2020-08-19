#include "shell.h"

/**
 * main- Simple shell that interpretates a single command line
 * prints a prompt and waits for the user to input a command, if the
 * command is accepted, will return its result.
 * @argc: Number of arguments
 * @argv: Array of arguments
 * @env: Array of variables
 * Return: 0 when the loop is finished by command exit or interrupted.
 */
int main(int argc, char *argv[], char *env[])
{
	int read = 0, is_builtin = 0;
	char *p_name = argv[0], *command_line = NULL;
	char **token_array = NULL;
	char *command_file = NULL;
	(void)argc;

	p_name = argv[0];
	signal(SIGINT, signal_handler);
	while (read != -1)
	{
		if (isatty(STDIN_FILENO) == 1)
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

/**
 * read_line - Reads an entire line from stream, storing the address of the
 * buffer containing the text
 * @rd: number of characters read.
 * Return: return the number of characters read, including the delimiter
 * character, but not including the terminating null byte
 */
char *read_line(int *rd)
{
	size_t size = 0;
	char *line = NULL;
	*rd = getline(&line, &size, stdin);

	if (*rd == -1)
	{
		free(line);
		line = NULL;
		/*perror("getline");*/
		exit(EXIT_SUCCESS);
	}
	return (line);
}

/**
 * start_new_process - Runs the tokenized command through execve and
 * return the command result if its valid.
 * @arg: Tokenized input.
 * @env: Array of enviroment variables.
 * @command_file: Path the to execute a command if its returned by function.
 * @p_name: Program name.
 * Return: If the command was successful, will show result, else run loop again
 */

int start_new_process(char **arg, char **env, char *command_file, char *p_name)
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
		if (execve(arg[0], arg, env) == -1)
		{
			if (command_file)
			{
				if (execve(command_file, arg, env) == -1)
				{
					free(command_file), free_pointer_array(arg);
					print_error(arg, p_name);
					exit(EXIT_FAILURE);
				}
			}
			/*perror(NULL);*/
			print_error(arg, p_name);
			free_pointer_array(arg);
			exit(EXIT_SUCCESS);
		}
	default:
		do {
			if (waitpid(pid, &status, WUNTRACED) == -1)
			{
				perror("waitpid error");
				return (0);
			}
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
	return (1);
}
