#ifndef MAIN_H
#define MAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/* Prototyoes for helper functions */
int length(char *str);
int str_cmp(char *s1, char *s2);
int execut(char *cmd);
void ft_free(char *str);

#endif /* MAIN_H */
