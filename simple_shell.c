#include “shell.h”
int main(int argc, char *argv[])
{
  int signal = 1; /*REVISAR*/
  char *line;
  (void)argc;
  /*loop hasta que reciba el signal de salida*/
  do
  {
    /*imprimir prompt*/
    write(STDOUT_FILENO, “$ “, 2);
    /*funcaion para recibir argumentos y almacenar linea de argumentos*/
    line = read_line(); /*REVISAR*/
    /*tokenizar argumentos*/
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