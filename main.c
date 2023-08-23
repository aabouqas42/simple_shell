#include "main.h"

/**
 * main - Entry point
 * @argc: The number of command line arguments
 * @argv: An array of strings containing the arguments
 *
 * Return: Always 0 (Success)
 */
int main(int argc, char *argv[])
{
	unsigned long size = 0;
	char *cmd;

	while (1)
	{
		write(1, "#cisfun$ ", 9);

		getline(&cmd, &size, stdin);

		cmd[strlen(cmd) - 1] = '\0';

		if (strcmp(cmd, "exit") == 0)
			break;

		int pid = fork();

		if (pid == 0)
		{
			int result = execut(cmd);

			if (result == -1)
			{
				perror(argv[0]);
				exit(EXIT_FAILURE);
			}
			exit(EXIT_SUCCESS);
		}
		else if (pid > 0)
		{
			waitpid(pid, NULL, 0);
		}
		else
		{
			exit(EXIT_FAILURE);
		}
	}

	free(cmd);

	return (0);
}
