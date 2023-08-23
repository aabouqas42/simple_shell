#include "main.h"

/**
 * main - entry point of the shell program
 *
 * Return: 0 on success
 */
int main(void)
{
	char *buffer = NULL;
	char **av = NULL;
	char *PATH = NULL;
	char *copy = NULL;
	char *full_path_buffer = NULL;
	int exit_status = 0;

	while (1)
	{
		prompt();
		buffer = _read();
		if (!buffer)
			continue;
		av = tokenize(buffer);
		if (!av)
		{
			free(buffer);
			continue;
		}
		PATH = _getenv("PATH");
		if (!PATH)
		{
			perror("Error");
			continue;
		}
		full_path_buffer = _fullpathbuffer(av, PATH, copy);
		if (checkbuiltins(av, buffer, exit_status) == 1)
			continue;
		exit_status = _forkprocess(av, buffer, full_path_buffer);
	}
	return (0);
}
