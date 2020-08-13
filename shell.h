#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

void signal_handler(int n);
char *read_line(int *);
char **tokenize(char *);
int start_new_process(char **arguments, char **env);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_pointer_array(char **token_array);
int _strcmp(char *s1, char *s2);
char *str_concat(char *s1, char *s2);
char **find_path(char *name, char **envp);
char *path(char **token_array, char *env[]);

#endif