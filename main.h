#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void print_prompt(void);
char *read_line(void);
void execute_command(char *command);

#endif /* MAIN_H */
