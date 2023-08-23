#include "shell.h"

/**
 * cmp_env_name - compares the environment vars
 * @nenv: env variable
 * @name: the name passed
 * Return: 0 on fail
 */
int cmp_env_name(const char *nenv, const char *name)
{
	int i;

	for (i = 0; nenv[i] != '='; i++)
	{
		if (nenv[i] != name[i])
		{
			return (0);
		}
	}

	return (i + 1);
}

/**
 * _getenv - gets env variable
 * @name: name of env variable
 * @_environ: the environment variable
 * Return: value of env variable
 */
char *_getenv(const char *name, char **_environ)
{
	int i, mov = 0;
	char *ptr_env = NULL;

	for (i = 0; _environ[i]; i++)
	{
		mov = cmp_env_name(_environ[i], name);
		if (mov)
		{
			ptr_env = _environ[i];
			break;
		}
	}

	return (ptr_env + mov);
}

/**
 * print_env - prints env variables
 * @shell_data: struct
 * Return: 1 on success
 */
int print_env(arg_list *shell_data)
{
	int i, j;

	for (i = 0; shell_data->_environ[i]; i++)
	{

		for (j = 0; shell_data->_environ[i][j]; j++)
			;

		write(STDOUT_FILENO, shell_data->_environ[i], j);
		write(STDOUT_FILENO, "\n", 1);
	}
	shell_data->status = 0;

	return (1);
}
