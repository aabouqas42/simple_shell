#include "shell.h"

/**
 * free_data - frees struct
 * @shell_data: Struct
 * Return: void
 */
void free_data(arg_list *shell_data)
{
	unsigned int i;

	for (i = 0; shell_data->_environ[i]; i++)
	{
		free(shell_data->_environ[i]);
	}

	free(shell_data->_environ);
	free(shell_data->pid);
}

/**
 * set_data - initialize struct
 * @shell_data: Struct
 * @av: argument vector
 * Return: void
 */
void set_data(arg_list *shell_data, char **av)
{
	unsigned int i;

	shell_data->av = av;
	shell_data->input = NULL;
	shell_data->args = NULL;
	shell_data->status = 0;
	shell_data->counter = 1;

	for (i = 0; environ[i]; i++)
		;

	shell_data->_environ = malloc(sizeof(char *) * (i + 1));

	for (i = 0; environ[i]; i++)
	{
		shell_data->_environ[i] = _strdup(environ[i]);
	}

	shell_data->_environ[i] = NULL;
	shell_data->pid = _itoa(getpid());
}

/**
 * main - Entry point
 * @ac: argument count
 * @av: argument vector
 *
 * Return: 0
 */
int main(int ac, char **av)
{
	arg_list shell_data;
	(void) ac;

	signal(SIGINT, handle_signal);
	set_data(&shell_data, av);
	loop_sh(&shell_data);
	free_data(&shell_data);
	if (shell_data.status < 0)
		return (255);
	return (shell_data.status);
}
