#include "main.h"

/**
 * tokenize - tokenizes a string
 * @buffer: string to tokenize
 *
 * Return: pointer to an array of tokens
 */
char **tokenize(char *buffer)
{
	int i, count = 0;
	char **av, *token, *copy;

	if (buffer == NULL)
		return (NULL);

	count = _splitstring(buffer);
	av = malloc(sizeof(char *) * (count + 1));
	if (av == NULL)
		return (NULL);
	copy = _strdup(buffer);
	token = strtok(copy, " \t");
	for (i = 0; token != NULL; i++)
	{
		av[i] = _strdup(token);
		token = strtok(NULL, " \t");
	}
	av[i] = NULL;
	free(copy);
	return (av);
}

/**
 * _splitPATH - splits the PATH string into individual directories
 * @str: PATH string
 *
 * Return: number of directories
 */
int _splitPATH(char *str)
{
	int count = 0;
	char *token;

	token = strtok(str, ":");
	while (token != NULL)
	{
		count++;
		token = strtok(NULL, ":");
	}
	return (count);
}

/**
 * _PATHstrcmp - compares two strings, ignoring '/' at the end of s2
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if the strings are equal, negative value if s1 is less than s2,
 * positive value if s1 is greater than s2
 */
int _PATHstrcmp(const char *s1, const char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return ((s1[i] - s2[i]));
	}
	if (s2[i - 1] == '/')
		return (0);

	return ((s1[i] - s2[i]));
}

/**
 * _concat - concatenates strings to form a file path
 * @tmp: temporary buffer for the concatenated string
 * @av: array of user strings
 * @tok: current token from PATH
 *
 * Return: pointer to the concatenated string
 */
char *_concat(char *tmp, char **av, char *tok)
{
	_memset(tmp, 0, 256);
	_strcat(tmp, tok);
	_strcat(tmp, "/");
	_strcat(tmp, av[0]);
	return (tmp);
}
