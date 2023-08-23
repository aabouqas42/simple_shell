#include "main.h"

/**
  *length - function thats calcuate length of string
  *@str: the string to be calcuate the length
  *Return: the length of str
  */

int length(char *str)
{
	int i;

	while (str[i])
		i++;
	return (i);
}

/**
  *str_cmp - function thats compaire two strings
  *@s1: first string
  *@s2: second string
  *Return: the difference between s1 and s2
  */
int str_cmp(char *s1, char *s2)
{
	int i = 0;

	while (s1[i] && s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
	i++;
	}
	return (0);
}

/**
  *ft_strcat - function thats concatenate two strings
  *@dest: first string
  *@str: the string to be concatenation
  *Retutn: Nothing
  */

void ft_strcat(char *dest, char *str)
{
	int i = 0;
	int len = length(dest);

	while (str[i])
	{
		dest[len] = str[i];
		len++;
		i++;
	}
	dest[len] = '\0';


/**
  *execut - function thats execut a command
  *@cmd: a sting contains a command
  *Return: state if the executation sucsses return 1 or
  */

int execut(char *cmd)
{
	int state, i;
	char **args;
	char *str;

	str = strtok(cmd, " ");
	args = malloc(length(cmd) + 1);
	i = 0;
	while (str != NULL && i < length(cmd))
	{
		args[i] = str;
		str = strtok(NULL, " ");
		i++;
	}
	args[i] = NULL;
	state = system(cmd);
	free(args);
	return (state);
}
