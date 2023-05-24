#include "main.h"

/**
 * str_duplicate - Duplicates a string.
 * @src: The string to duplicate.
 *
 * Return: NULL if size is 0 or if memory is not available, otherwise a pointer
 *         to the duplicated string.
 */
char *str_duplicate(char *src)
{
	if (src == NULL)
		return (NULL);

	unsigned int length = 0;

	while (src[length] != '\0')
		length++;

	char *duplicate = malloc((length + 1) * sizeof(char));

	if (duplicate == NULL)
		return (NULL);

	for (unsigned int i = 0; i <= length; i++)
		duplicate[i] = src[i];

	return (duplicate);
}

/**
 * str_concatenate - Concatenates two strings.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return: NULL if size is 0, otherwise a pointer to the concatenated string.
 */
char *str_concatenate(char *str1, char *str2)
{
	unsigned int len1 = 0, len2 = 0;

	if (str1 != NULL)
	{
		while (str1[len1] != '\0')
			len1++;
	}
	if (str2 != NULL)
	{
		while (str2[len2] != '\0')
			len2++;
	}
	unsigned int total_length = len1 + len2 + 2;
	char *result = malloc(total_length * sizeof(char));

	if (result == NULL)
		return (NULL);

	unsigned int i = 0, j = 0;

	if (str1 != NULL)
	{
		for (; i < len1; i++)
			result[i] = str1[i];
	}
	result[i++] = '/';
	if (str2 != NULL)
	{
		for (; j < len2; j++)
			result[i + j] = str2[j];
	}
	result[i + j] = '\0';

	return (result);
}

/**
 * string_length - Calculates the length of a string.
 * @str: The string.
 *
 * Return: The length of the string.
 */
int string_length(char *str)
{
	int len = 0;

	while (str[len] != '\0')
		len++;

	return (len);
}

/**
 * check_empty - Checks if the string is empty.
 * @str: The string to check.
 *
 * Return: -1 if the string is different, 0 otherwise.
 */
int check_empty(char *str)
{
	int index = 0;

	if (str[0] == ' ' || str[0] == '\t')
	{
		while (str[index] == ' ')
			index++;
	}

	if (str[index] == '\n' && str[index + 1] == '\0')
		return (0);

	return (-1);
}

/**
 * compare_strings - Compares two strings.
 * @str1: The first string.
 * @str2: The second string.
 * @length: The number of characters to compare.
 *
 * Return: -1 if the strings are different, 0 otherwise.
 */
int compare_strings(char *str1, const char *str2, int length)
{
	for (int index = 0; index < length; index++)
	{
		if (str1[index] != str2[index])
			return (-1);
	}

	return (0);
}
