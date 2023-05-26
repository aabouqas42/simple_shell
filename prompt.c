#include "main.h"

/**
 * prompt - writes a prompt
 *
 * Return: 0 on success
 */
int prompt(void)
	{
	char *prompt = "$ ";
	ssize_t write_count = 0;

	if (isatty(STDIN_FILENO) == 1)
	{
	write_count = write(STDOUT_FILENO, prompt, 2);
	if (write_count == -1)
	exit(0);
	}
	return (0);
	}
