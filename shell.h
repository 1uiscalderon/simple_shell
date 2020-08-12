#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

char *read_line(void);
char **tokenize(char *line);
int start_new_process(char **arguments, char **env);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

#endif