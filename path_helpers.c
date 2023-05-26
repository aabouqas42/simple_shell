#include "main.h"

/**
 * _getenv - gets the value of an environment variable
 * @name: name of the environment variable
 *
 * Return: value of the environment variable
 */
char *_getenv(const char *name)
{
	int i, j;
	char *env_name, *env_value;

	for (i = 0; environ[i] != NULL; i++)
	{
		env_name = environ[i];
		for (j = 0; name[j] == env_name[j] && name[j] != '\0'; j++)
			if (name[j] == '\0')
			{
				env_value = environ[i] + j + 1;
				return (env_value);
			}
	}
	return (NULL);
}

/**
 * _env - prints the current environment
 *
 * Return: 0 on success
 */
int _env(void)
{
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		_puts(environ[i]);
		_putchar('\n');
	}
	return (0);
}

/**
 * _puts - writes a string to stdout
 * @str: string to write
 */
void _puts(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes a character to stdout
 * @c: character to write
 *
 * Return: 1 on success, -1 on failure
 */
int _putchar(char c)
{
	return ((write(STDOUT_FILENO, &c, 1)));
}

/**
 * _memset - fills a memory block with a constant byte
 * @s: pointer to the memory block
 * @b: constant byte
 * @n: number of bytes to fill
 *
 * Return: pointer to the memory block
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		s[i] = b;
	return (s);
}
