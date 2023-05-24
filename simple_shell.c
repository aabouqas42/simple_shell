#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100
/**
  * main - program thats interpreter UNIX comand line
  *
  * Return: always 0
  */
int main(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		printf("#cisfun$ ");
		if (fgets(command, sizeof(command), stdin) == NULL)
			break;

		command[strcspn(command, "\n")] = '\0';

		if (strcmp(command, "exit") == 0)
			break;

		pid_t child_pid = fork();

		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}

		if (child_pid == 0)
		{
			execlp(command, command, (char *)NULL);
			perror(command);
			exit(EXIT_FAILURE);
		} else
		{
			int status;

			waitpid(child_pid, &status, 0);
			if (status != 0)
				printf("%s: No such file or directory\n", command);
		}
	}

	return (0);
}
