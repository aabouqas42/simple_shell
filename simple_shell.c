#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUFFER_SIZE 1024
/**
  * main - program thats interpreter UNIX command line
  *
  * Return: 0
  */
int main(void)
{
	char input[BUFFER_SIZE];
	char *prompt = "simple_shell> ";

	while (1)
	{
		printf("%s", prompt);
		if (fgets(input, BUFFER_SIZE, stdin) == NULL)
		{
			printf("\n");
			break;
		}

		input[strcspn(input, "\n")] = '\0';

		pid_t pid = fork();

		if (pid < 0)
		{
			fprintf(stderr, "fork failed\n");
			return (1);
		} else if (pid == 0)
		{
			if (execlp(input, input, NULL) == -1)
			{
				fprintf(stderr, "Command not found: %s\n", input);
				exit(1);
			}
		} else
		{
			wait(NULL);
		}
	}
	return (0);
}
