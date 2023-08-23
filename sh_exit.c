#include "shell.h"

/**
 * sh_exit - terminate shell
 * @shell_data: Struct
 * Return: 0 on success
 */
int sh_exit(arg_list *shell_data)
{
	unsigned int ustatus;
	int is_digit;
	int str_len;
	int big_number;

	if (shell_data->args[1] != NULL)
	{
		ustatus = _atoi(shell_data->args[1]);
		is_digit = _isdigit(shell_data->args[1]);
		str_len = _strlen(shell_data->args[1]);
		big_number = ustatus > (unsigned int)INT_MAX;
		if (!is_digit || str_len > 10 || big_number)
		{
			fetch_error(shell_data, 2);
			shell_data->status = 2;
			return (1);
		}
		shell_data->status = (ustatus % 256);
	}
	return (0);
}

/**
 * handle_signal - handle the crtl + c
 * @sig: signal
 */
void handle_signal(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\nshell$ ", 8);
}
