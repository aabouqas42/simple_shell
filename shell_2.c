#include "main.h"

/**
 * print_no_such_error - Prints an error message for
 * "no such file or directory" error.
 * @str: The string.
 * @hist: The history of commands.
 */
void print_no_such_error(char *str, int hist)
{
	char *prefix = ": ";
	char *suffix = "not found\n";

	printf("%s%s", sh_call, prefix);
	printf("%d%s%s%s", hist, prefix, str, suffix);
	state = 127;
}

/**
 * print_permission_error - Prints an error message
 * for "permission denied" error.
 * @str: The string.
 * @hist: The history of commands.
 */
void print_permission_error(char *str, int hist)
{
	char *prefix = ": ";
	char *suffix = "Permission denied\n";

	printf("%s%s", sh_call, prefix);
	printf("%d%s%s%s", hist, prefix, str, suffix);
	state = 126;
}

/**
 * check_error - Checks and handles the error based on errno.
 * @str: The string.
 * @hist: The history of commands.
 */
void check_error(char *str, int hist)
{
	int length = _strlen(str);

	str[length] = '\0';

	if (errno == ENOENT)
		print_no_such_error(str, hist);

	else if (errno == EACCES)
		print_permission_error(str, hist);
}

/**
 * get_environment_variable - Retrieves an environment variable
 * if it matches the name.
 * @name: The name of the environment variable.
 *
 * Return: The environment variable if found, otherwise NULL.
 */
char *get_environment_variable(char *name)
{
	int i, len = 0;

	while (name[len])
		len++;

	if (environ == NULL)
		return (NULL);

	for (i = 0; environ[i]; i++)
	{
		if (compare_strings(environ[i], name, len) == 0)
		{
			if (string_length(environ[i]) > 5)
				return (environ[i]);
		}
	}

	return (NULL);
}

/**
 * print_environment - Prints the environment.
 * @str: The string from getline.
 *
 * Return: 1 on success, 0 if failed.
 */
int print_environment(char *str)
{
	int i, j;

	if (!str)
		return (0);

	for (i = 0; environ[i]; i++)
	{
		for (j = 0; environ[i][j]; j++)
		{
			putchar(environ[i][j]);
		}
		putchar(10);
	} return (1);
}
