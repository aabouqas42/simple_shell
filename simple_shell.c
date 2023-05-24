#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 100
/**
 * execute_command - Executes a command in a child process
 * @command: The command to execute
 */
void execute_command(char *command)
{
	pid_t pid = fork();

	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (pid == 0)
	{
		char *args[MAX_COMMAND_LENGTH];
		int i;

		args[0] = strtok(command, " ");
		i = 1;

		while (args[i - 1] != NULL && i < MAX_COMMAND_LENGTH)
		{
			args[i] = strtok(NULL, " ");
			i++;
		}

		if (execve(args[0], args, NULL) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	} else
	{
		int status;

		waitpid(pid, &status, 0);

		if (status != 0)
		{
			printf("%s: command not found\n", command);
		}
	}
}
/**
 * run_shell - Runs the UNIX command line shell
 */
void run_shell(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		printf("#cisfun$ ");
		fflush(stdout);

		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			printf("\n");
			break;
		}

		command[strcspn(command, "\n")] = '\0';

		execute_command(command);
	}
}
/**
 * main - Entry point of the program
 *
 * Return: Always 0
 */
int main(void)
{
	run_shell();
	return (EXIT_SUCCESS);
}
