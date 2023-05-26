#include "main.h"

/**
 * _strdup - duplicates a string
 * @str: string to duplicate
 *
 * Return: pointer to duplicated string
 */
char *_strdup(char *str)
{
	int len, i;
	char *dup_str;

	if (!str)
		return (NULL);

	len = _strlen(str);
	dup_str = malloc(sizeof(char) * (len + 1));
	if (!dup_str)
		return (NULL);

	for (i = 0; i < len; i++)
		dup_str[i] = str[i];
	dup_str[i] = '\0';
	return (dup_str);
}

/**
 * _splitstring - splits a string into an array of strings
 * @str: string to split
 *
 * Return: number of substrings
 */
int _splitstring(char *str)
{
	int count = 0;
	char *token;

	token = strtok(str, " \t");

	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " \t");
	}
	return (count);
}

/**
 * _strcmp - compares two strings
 * @s1: first string
 * @s2: second string
 *
 * Return: 0 if the strings are equal, negative value if s1 is less than s2,
 * positive value if s1 is greater than s2
 */
int _strcmp(const char *s1, const char *s2)
{
	int i;

	for (i = 0; s1[i] != '\0'; i++)
	{
		if (s1[i] != s2[i])
			return ((s1[i] - s2[i]));
	}
	return ((s1[i] - s2[i]));
}

/**
 * _strcat - concatenates two strings
 * @dest: destination string
 * @src: source string
 *
 * Return: pointer to the resulting string
 */
char *_strcat(char *dest, char *src)
{
	int dest_len = _strlen(dest);
	int i;

	for (i = 0; src[i] != '\0'; i++)
		dest[dest_len + i] = src[i];
	dest[dest_len + i] = '\0';
	return (dest);
}

/**
 * _strlen - returns the length of a string
 * @s: string
 *
 * Return: length of the string
 */
int _strlen(char *s)
{
	int len = 0;

	while (s[len] != '\0')
		len++;
	return (len);
}
