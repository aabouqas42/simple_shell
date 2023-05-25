#include "main.h"

void int_to_str(int);

/**
 * main - Start the simple shell
 * @ac: Number of args
 * @ag: Args
 * Return: state
 */

int main(int ac, char **ag)
{
	char *prompt = "\033[1;35m$\033[0m ";
	char *str = NULL;
	char **array;
	int command, i;
	size_t n = 0;
	struct stat st;
	int hist = 1;

	if (ac <= 1)
		sh_call = ag[0];
	state = 0;
	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, prompt, 13);
		command = getline(&str, &n, stdin);
		if (command == EOF)
		{
			if (isatty(STDIN_FILENO))
				_putchar(10);
			our_exit(str);
		}
		if (command != -1)
		{
			if (chk_builtin(str) == 0)
			{
				array = chk_path(str);
				if (stat(array[0], &st) == 0)
					_execve(array, hist, str);
				else
					chk_error(str, hist);

				for (i = 0; array[i]; i++)
					free(array[i]);

				free(array);
			}
		}
		else
			chk_error(str, hist);
		hist++;
	}
	free(str);
	return (state);
}

/**
 * int_to_str - Convert and print an int to string
 * @i: number to print.
 */

void int_to_str(int i)
{
	int dig = 0, cpi = i, pot = 1;

	while (i > 0)
	{
		i = i / 10;
		dig++;
	}
	while (dig > 1)
	{
		pot *= 10;
		dig--;
	}
	for (; pot > 0; pot /= 10)
	{
		_puterror((cpi / (pot)) + 48);
		cpi %= pot;
	}
}
