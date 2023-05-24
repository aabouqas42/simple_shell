#include "main.h"

/**
 * print_prompt - Prints the shell prompt
 */
void print_prompt(void)
{
	printf("#cisfun$ ");
}

/**
 * read_line - Reads a line of input from the user
 * Return: The input line as a string
 */
char *read_line(void)
{
	char *line = NULL;
	size_t bufsize = 0;
	ssize_t characters_read;

	characters_read = getline(&line, &bufsize, stdin);
	if (characters_read == -1)
	{
		if (feof(stdin))
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		} else
		{
			perror("getline");
			exit(EXIT_FAILURE);
		}
	}

	return (line);
}

/**
 * execute_command - Executes a command
 * @command: The command to execute
 */
void execute_command(char *command)
{
	int status;
	pid_t child_pid;
	char **argv = NULL;
	char *envp[] = {NULL};

	argv = malloc(2 * sizeof(char *));
	if (argv == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	argv[0] = command;
	argv[1] = NULL;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	} else if (child_pid == 0)
	{
		if (execve(command, argv, envp) == -1)
		{
			perror("execve");
			exit(EXIT_FAILURE);
		}
	} else
	{
		waitpid(child_pid, &status, 0);
	}
	free(argv);
}

/**
 * main - Program that executes a UNIX command line interpreter
 * Return: Always 0
 */
int main(void)
{
	char command[100];

	while (1)
	{
		printf("#cisfun$ ");
		if (fgets(command, sizeof(command), stdin) == NULL)
		{
			break;
		}
		command[strcspn(command, "\n")] = '\0';

		execute_command(command);
	}
	return (0);
}
