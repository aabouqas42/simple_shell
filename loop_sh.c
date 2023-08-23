#include "shell.h"

/**
 * loop_sh - infinite looping shell
 * @shell_data: Struct
 * Return: void
 */
void loop_sh(arg_list *shell_data)
{
	int loop, eof_input;
	char *input;

	loop = 1;
	while (loop == 1)
	{
		write(STDIN_FILENO, "($) ", 4);
		input = read_line(&eof_input);
		if (eof_input != -1)
		{
			input = comment_del(input);
			if (input == NULL)
				continue;

			if (syntax_err_checker(shell_data, input) == 1)
			{
				shell_data->status = 2;
				free(input);
				continue;
			}
			input = replace_variable(input, shell_data);
			loop = cmd_separator(shell_data, input);
			shell_data->counter += 1;
			free(input);
		}
		else
		{
			loop = 0;
			free(input);
		}
	}
}

/**
 * comment_del - delete comments from input
 * @in: input str
 * Return: input with no comments
 */
char *comment_del(char *in)
{
	int i, up_to;

	up_to = 0;
	for (i = 0; in[i]; i++)
	{
		if (in[i] == '#')
		{
			if (i == 0)
			{
				free(in);
				return (NULL);
			}

			if (in[i - 1] == ' ' || in[i - 1] == '\t' || in[i - 1] == ';')
				up_to = i;
		}
	}
	if (up_to != 0)
	{
		in = _realloc(in, i, up_to + 1);
		in[up_to] = '\0';
	}
	return (in);
}
