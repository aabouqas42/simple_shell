#include "shell.h"

/**
 * tokenize - tokenizes the input string
 * @input: input str
 * Return: tokens
 */
char **tokenize(char *input)
{
	size_t bsize;
	size_t i;
	char **tokens;
	char *token;

	bsize = TOK_BUFSIZE;
	tokens = malloc(sizeof(char *) * (bsize));
	if (tokens == NULL)
	{
		write(STDERR_FILENO, ": allocation error\n", 18);
		exit(EXIT_FAILURE);
	}

	token = _strtok(input, TOK_DELIM);
	tokens[0] = token;

	for (i = 1; token != NULL; i++)
	{
		if (i == bsize)
		{
			bsize += TOK_BUFSIZE;
			tokens = _realloc_dup(tokens, i, sizeof(char *) * bsize);
			if (tokens == NULL)
			{
				write(STDERR_FILENO, ": allocation error\n", 18);
				exit(EXIT_FAILURE);
			}
		}
		token = _strtok(NULL, TOK_DELIM);
		tokens[i] = token;
	}

	return (tokens);
}

/**
 * character_swap - switch | and &
 * @input: input
 * @bool: state
 * Return: new string
 */
char *character_swap(char *input, int bool)
{
	int i;

	if (bool == 0)
	{
		for (i = 0; input[i]; i++)
		{
			if (input[i] == '|')
			{
				if (input[i + 1] != '|')
					input[i] = 16;
				else
					i++;
			}

			if (input[i] == '&')
			{
				if (input[i + 1] != '&')
					input[i] = 12;
				else
					i++;
			}
		}
	}
	else
	{
		for (i = 0; input[i]; i++)
		{
			input[i] = (input[i] == 16 ? '|' : input[i]);
			input[i] = (input[i] == 12 ? '&' : input[i]);
		}
	}
	return (input);
}

/**
 * node_add - add separators, command lines in the list
 * @head_s: separator list head
 * @head_l: command line list head
 * @input: input string
 * Return: void
 */
void node_add(separator_list **head_s, list_string **head_l, char *input)
{
	int i;
	char *line;

	input = character_swap(input, 0);

	for (i = 0; input[i]; i++)
	{
		if (input[i] == ';')
			separator_node(head_s, input[i]);

		if (input[i] == '|' || input[i] == '&')
		{
			separator_node(head_s, input[i]);
			i++;
		}
	}

	line = _strtok(input, ";|&");
	do {
		line = character_swap(line, 1);
		line_node(head_l, line);
		line = _strtok(NULL, ";|&");
	} while (line != NULL);

}

/**
 * next_command - find next command line stored
 * @list_s: separator list
 * @list_l: command line list
 * @shell_data: Struct
 * Return: void
 */
void next_command(separator_list **list_s, list_string **list_l,
	arg_list *shell_data)
{
	int loop_sep;
	separator_list *ls_s;
	list_string *ls_l;

	loop_sep = 1;
	ls_s = *list_s;
	ls_l = *list_l;

	while (ls_s != NULL && loop_sep)
	{
		if (shell_data->status == 0)
		{
			if (ls_s->separator == '&' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '|')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		else
		{
			if (ls_s->separator == '|' || ls_s->separator == ';')
				loop_sep = 0;
			if (ls_s->separator == '&')
				ls_l = ls_l->next, ls_s = ls_s->next;
		}
		if (ls_s != NULL && !loop_sep)
			ls_s = ls_s->next;
	}

	*list_s = ls_s;
	*list_l = ls_l;
}

/**
 * cmd_separator - split commands
 * @shell_data: Struct
 * @input: input
 * Return: 0 to exit, 1 to continue
 */
int cmd_separator(arg_list *shell_data, char *input)
{

	separator_list *head_s, *list_s;
	list_string *head_l, *list_l;
	int loop;

	head_s = NULL;
	head_l = NULL;

	node_add(&head_s, &head_l, input);

	list_s = head_s;
	list_l = head_l;

	while (list_l != NULL)
	{
		shell_data->input = list_l->line;
		shell_data->args = tokenize(shell_data->input);
		loop = find_builtin(shell_data);
		free(shell_data->args);

		if (loop == 0)
			break;

		next_command(&list_s, &list_l, shell_data);

		if (list_l != NULL)
			list_l = list_l->next;
	}

	free_seperator(&head_s);
	free_list_string(&head_l);

	if (loop == 0)
		return (0);
	return (1);
}
