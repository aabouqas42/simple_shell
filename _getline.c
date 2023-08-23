#include "shell.h"

/**
 * assign_line_var - assigns line var for _get_line
 * @lineptr: string pointer
 * @buffer: stores input
 * @n: size of line
 * @j: size of buffer
 */
void assign_line_var(char **lineptr, size_t *n, char *buffer, size_t j)
{

	if (*lineptr == NULL)
	{
		if  (j > BUFSIZE)
			*n = j;

		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else if (*n < j)
	{
		if (j > BUFSIZE)
			*n = j;
		else
			*n = BUFSIZE;
		*lineptr = buffer;
	}
	else
	{
		_strcpy(*lineptr, buffer);
		free(buffer);
	}
}
/**
 * _get_line - gets input
 * @lineptr: string input
 * @n: size of lineptr
 * @stream: stream to read from
 * Return: number of bytes
 */
ssize_t _get_line(char **lineptr, size_t *n, FILE *stream)
{
	char *buffer;
	int i;
	static ssize_t input;
	char t = 'z';
	ssize_t n_bytes;

	if (input == 0)
		fflush(stream);
	else
		return (-1);
	input = 0;

	buffer = malloc(sizeof(char) * BUFSIZE);
	if (buffer == 0)
		return (-1);
	while (t != '\n')
	{
		i = read(STDIN_FILENO, &t, 1);
		if (i == -1 || (i == 0 && input == 0))
		{
			free(buffer);
			return (-1);
		}
		if (i == 0 && input != 0)
		{
			input++;
			break;
		}
		if (input >= BUFSIZE)
			buffer = _realloc(buffer, input, input + 1);
		buffer[input] = t;
		input++;
	}
	buffer[input] = '\0';
	assign_line_var(lineptr, n, buffer, input);
	n_bytes = input;
	if (i != 0)
		input = 0;
	return (n_bytes);
}
