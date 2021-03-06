#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <string.h>
#include <signal.h>

extern char **environ;
void signal_handler(int n);
char *read_line(int *);
char **tokenize(char *);
int start_new_process(char **arguments, char **env, char *, char *s);
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);
void free_pointer_array(char **token_array);
int _strcmp(char *s1, char *s2);
char *str_concat(char *s1, char *s2);
char **find_path(char **);
char *path(char **, char **);
int built_ins(char **, char *env[], char *name);
int token_counter(char *str, char *delim);
int find_delimiter(char *delim, char str_char);
char **strtok_arr(char *str, char *delim);
int _strlen(char *s);
char *_strdup(char *str);
void *_calloc(unsigned int nmemb, unsigned int size);
void print_env_error(char **arg);
void print_error(char **arg, char *name);
void print_exit_error(char **args, char *p_name);
#endif
