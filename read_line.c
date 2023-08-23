#include "shell.h"

/**
 * read_line - fetches the input stt
 * @eof_input: return value of getline function
 * Return: input str
 */
char *read_line(int *eof_input)
{
	char *input = NULL;
	size_t bufsize = 0;

	*eof_input = getline(&input, &bufsize, stdin);

	return (input);
}
