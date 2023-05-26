#include "main.h"

/**
 * prompt - writes a prompt
 *
 * Return: 0 on success
 */
int prompt(void)
{
	char *prompt = "$ ";
	ssize_t writecount = 0;

	if (isatty(STDIN_FILENO))
	{
		writecount = write(STDOUT_FILENO, prompt, 2);
		if (writecount == -1)
			exit(0);
	}
	return (0);
}
