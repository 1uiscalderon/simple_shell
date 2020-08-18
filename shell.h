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

extern char **environ;
void signal_handler(int n);
char *read_line(int *);
char **tokenize(char *);
int start_new_process(char **arguments, char **env, char *);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_pointer_array(char **token_array);
int _strcmp(char *s1, char *s2);
char *str_concat(char *s1, char *s2);
char **find_path(char **);
char *path(char **, char **);
int built_ins(char **, char *env[]);
int token_counter(char *str, char *delim);
char **strtok_arr(char *str, char *delim);
int _strlen(char *s);
char *_strdup(char *str);
void *_calloc(unsigned int nmemb, unsigned int size);
int find_delimiter(char *delim, char str_char);

#endif