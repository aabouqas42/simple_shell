#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 1024
/**
  * main - program thats execute UNIX command line
  *
  * Return: always 0
  */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];
	char prompt[] = "#cisfun$ ";

	while (1)
	{
		pid_t pid;

		printf("%s", prompt);

		if (fgets(command, sizeof(command), stdin) == NULL)
			break;

		command[strcspn(command, "\n")] = '\0';

		if (strcmp(command, "exit") == 0)
			break;

		pid = fork();

		if (pid < 0)
		{
			perror("Fork error");
			exit(EXIT_FAILURE);
		} else if (pid == 0)
		{
			execlp(command, command, (char *) NULL);
			perror("Execution error");
			exit(EXIT_FAILURE);
		} else
		{
			int status;

			waitpid(pid, &status, 0);
		}
	}

	return (0);
}
