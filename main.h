#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>

extern char **environ;
int state;


int _strlen(char *s);
char *_strdup(char *str);
int my_strcmp(char *s1, const char *s2, int len);
char *str_concat(char *s1, char *s2);
int count_delimiters(char *str, char *delim);
char *concat_strings(const char *s1, const char *s2);


void chk_error(char *str, int hist);
void error_no_such(char *str, int hist);
void error_permission(char *str, int hist);


char *get_env(char *name);
void print_env(char *str);


void execute(char **args, int hist, char *line);
int check_builtin(char *word);
char **check_path(char *str);
char *clean_path(char *path_env);
char **create_buffer(char *str, char *delim);


typedef struct builtin_s {
    char *command;
    void (*function)(char *);
} builtin;


void our_exit(char *arg);

#endif /* MAIN_H */
