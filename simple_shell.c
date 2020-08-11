#include “shell.h”
int main(int argc, char *argv[])
{
	int signal = 1; /*REVISAR*/
	char *line;
	char *commands(void) argc;
	/*loop hasta que reciba el signal de salida*/
	do
	{
		/*imprimir prompt*/
		write(STDOUT_FILENO, “$ “, 2);
		/*funcaion para recibir argumentos y almacenar linea de argumentos*/
		line = read_line(); /*REVISAR*/
		commands = tokenize(line);
		/*crear el proceso hijo*/
		/*opciones para hijo*/
		/*ejecutar comando, environment??*/
		/*opciones para padre*/
		/*esperar al hijo*/
		/*liberar memoria*/
		free(line);
	} while (signal) /*REVISAR*/
			 /*exit*/
}
char *read_line(void)
{
	int rd;
	ssize_t bufsize = 0;
	char *line = NULL;
	rd = getline(&line, &buf, stdin);
	if (rd == -1)
	{
		perror(“getline”); /*revisar*/
	}
	return (line);
}

char **tokenize(char *line)
{
	int buff = BUFFSIZE, i; /* posicion del string */
	char *node;
	char **nodes = malloc(BUFFSIZE * sizeof(char *));

	if (nodes == NULL)
	{
		perror(“Could not allocate memory”);
		exit(EXIT_FAILURE);
	}
	node = strtok(line, " "); /* Solo dividir por espacios" */
	while (node)
	{
		nodes[i] = node;
		i++;
		node = strtok(NULL, " ");
	}
	nodes[i] = NULL;
	return (nodes);
}
