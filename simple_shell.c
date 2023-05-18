#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main() {
    char input[BUFFER_SIZE];
    char *prompt = "simple_shell> ";

    while (1) {
        printf("%s", prompt);

        // read user input
        if (fgets(input, BUFFER_SIZE, stdin) == NULL) {
            // handle end of file condition
            printf("\n");
            break;
        }

        // remove trailing newline character
        input[strcspn(input, "\n")] = '\0';

        // execute command
        pid_t pid = fork();
        if (pid < 0) {
            fprintf(stderr, "fork failed\n");
            return 1;
        } else if (pid == 0) {
            // child process
            if (execlp(input, input, NULL) == -1) {
                fprintf(stderr, "Command not found: %s\n", input);
                exit(1);
            }
        } else {
            // parent process
            wait(NULL);
        }
    }

    return 0;
}
