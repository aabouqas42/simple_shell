#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
		fgets(command, sizeof(command), stdin);
		if (feof(stdin))
		{
			printf("\n");
			break;
		}
		char *args[MAX_COMMAND_LENGTH], *token;
		int i = 0;

		token = strtok(command, " \n");
		while (token != NULL)
		{
			args[i++] = token;
			token = strtok(NULL, " \n");
		}
		args[i] = NULL;
		pid_t pid = fork();

		if (pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		} else if (pid == 0)
		{

			execvp(args[0], args);
			perror("execvp");
			exit(EXIT_FAILURE);
		} else
		{
			int status;

			waitpid(pid, &status, 0);
		}
	} return (0);
}
