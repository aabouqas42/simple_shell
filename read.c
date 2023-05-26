#include "main.h"

/**
 * _read - reads stdin and stores it in a buffer
 *
 * Return: a pointer to the buffer
 */
char *_read(void)
{
	ssize_t read_count = 0;
	size_t n = 0;
	char *buffer = NULL;
	int i = 0;

	read_count = getline(&buffer, &n, stdin);
	if (read_count == -1)
	{
	free(buffer);
	if (isatty(STDIN_FILENO) != 0)
	write(STDOUT_FILENO, "\n", 1);
	exit(0);
	}
	if (buffer[read_count - 1] == '\n' || buffer[read_count - 1] == '\t')
	buffer[read_count - 1] = '\0';
	for (i = 0; buffer[i]; i++)
	{
	if (buffer[i] == '#' && buffer[i - 1] == ' ')
	{
	buffer[i] = '\0';
	break;
	}
	}
	return (buffer);
	}
