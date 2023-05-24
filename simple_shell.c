#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100

int main(void) {
    char command[MAX_COMMAND_LENGTH];
    char *args[MAX_COMMAND_LENGTH];
    int i, status;
    pid_t pid;

    while (1) {
        printf("#cisfun$ ");
        fgets(command, sizeof(command), stdin);
        if (feof(stdin)) {
            printf("\n");
            break;
        }

        // Tokenize the input command
        i = 0;
        args[i] = strtok(command, " \n");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " \n");
        }

        // Execute the command in a child process
        pid = fork();
        if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) {
            if (execvp(args[0], args) < 0) {
                perror("execvp");
                exit(EXIT_FAILURE);
            }
        }
        else {
            // Wait for the child process to complete
            waitpid(pid, &status, 0);
        }
    }

    return 0;
}}
