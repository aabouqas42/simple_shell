#include "shell.h"

/**
 * count_chars_rep - counts chars repeated
 * @input: string input
 * @i: index value
 * Return: repeated chars
 */
int count_chars_rep(char *input, int i)
{
	if (*(input - 1) == *input)
		return (count_chars_rep(input - 1, i + 1));

	return (i);
}

/**
 * syntax_error - gets syntax errors
 * @input: string input
 * @i: index value
 * @last: last character read
 * Return: error index
 */
int syntax_error(char *input, int i, char last)
{
	int count;

	count = 0;
	if (*input == '\0')
		return (0);

	if (*input == ' ' || *input == '\t')
		return (syntax_error(input + 1, i + 1, last));

	if (*input == ';')
		if (last == '|' || last == '&' || last == ';')
			return (i);

	if (*input == '|')
	{
		if (last == ';' || last == '&')
			return (i);

		if (last == '|')
		{
			count = count_chars_rep(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	if (*input == '&')
	{
		if (last == ';' || last == '|')
			return (i);

		if (last == '&')
		{
			count = count_chars_rep(input, 0);
			if (count == 0 || count > 1)
				return (i);
		}
	}

	return (syntax_error(input + 1, i + 1, *input));
}

/**
 * syntax_err_checker - checks for syntax error
 * @shell_data: Struct
 * @input: string input
 * Return: 1 if there is an error. 0 in other case
 */
int syntax_err_checker(arg_list *shell_data, char *input)
{
	int begin = 0;
	int f_char = 0;
	int i = 0;

	f_char = first_character(input, &begin);
	if (f_char == -1)
	{
		syntax_error_print(shell_data, input, begin, 0);
		return (1);
	}

	i = syntax_error(input + begin, 0, *(input + begin));
	if (i != 0)
	{
		syntax_error_print(shell_data, input, begin + i, 1);
		return (1);
	}

	return (0);
}

/**
 * first_character - finds first char index
 * @input: string input
 * @i: index value
 * Return: 1 on error
 */
int first_character(char *input, int *i)
{

	for (*i = 0; input[*i]; *i += 1)
	{
		if (input[*i] == ' ' || input[*i] == '\t')
			continue;

		if (input[*i] == ';' || input[*i] == '|' || input[*i] == '&')
			return (-1);

		break;
	}

	return (0);
}

/**
 * syntax_error_print - prints syntax error
 * @shell_data: Struct
 * @input: string input
 * @i: error index
 * @bool: boolean value
 * Return: void
 */
void syntax_error_print(arg_list *shell_data, char *input, int i, int bool)
{
	char *msg, *msg2, *msg3, *error, *counter;
	int length;

	if (input[i] == ';')
	{
		if (bool == 0)
			msg = (input[i + 1] == ';' ? ";;" : ";");
		else
			msg = (input[i - 1] == ';' ? ";;" : ";");
	}

	if (input[i] == '|')
		msg = (input[i + 1] == '|' ? "||" : "|");

	if (input[i] == '&')
		msg = (input[i + 1] == '&' ? "&&" : "&");

	msg2 = ": Syntax error: \"";
	msg3 = "\" unexpected\n";
	counter = _itoa(shell_data->counter);
	length = _strlen(shell_data->av[0]) + _strlen(counter);
	length += _strlen(msg) + _strlen(msg2) + _strlen(msg3) + 2;

	error = malloc(sizeof(char) * (length + 1));
	if (error == 0)
	{
		free(counter);
		return;
	}
	_strcpy(error, shell_data->av[0]);
	_strcat(error, ": ");
	_strcat(error, counter);
	_strcat(error, msg2);
	_strcat(error, msg);
	_strcat(error, msg3);
	_strcat(error, "\0");

	write(STDERR_FILENO, error, length);
	free(error);
	free(counter);
}
