#include "shell.h"

/**
 * env_checker - checks if input is an env var
 * @h: head of list
 * @in: input string
 * @arg_struct: struct
 * Return: void
 */
void env_checker(var_list **h, char *in, arg_list *arg_struct)
{
	int row, chr, j, lval;
	char **_envr;

	_envr = arg_struct->_environ;
	for (row = 0; _envr[row]; row++)
	{
		for (j = 1, chr = 0; _envr[row][chr]; chr++)
		{
			if (_envr[row][chr] == '=')
			{
				lval = _strlen(_envr[row] + chr + 1);
				add_var_node(h, j, _envr[row] + chr + 1, lval);
				return;
			}

			if (in[j] == _envr[row][chr])
				j++;
			else
				break;
		}
	}

	for (j = 0; in[j]; j++)
	{
		if (in[j] == ' ' || in[j] == '\t' || in[j] == ';' || in[j] == '\n')
			break;
	}

	add_var_node(h, j, NULL, 0);
}

/**
 * replace_variable - replaces str into vars
 * @input: input string
 * @shell_data: Struct
 * Return: string
 */
char *replace_variable(char *input, arg_list *shell_data)
{
	var_list *head, *indx;
	char *status, *new_input;
	int olen, nlen;

	status = _itoa(shell_data->status);
	head = NULL;

	olen = variable_checker(&head, input, status, shell_data);

	if (head == NULL)
	{
		free(status);
		return (input);
	}

	indx = head;
	nlen = 0;

	while (indx != NULL)
	{
		nlen += (indx->len_val - indx->len_var);
		indx = indx->next;
	}

	nlen += olen;

	new_input = malloc(sizeof(char) * (nlen + 1));
	new_input[nlen] = '\0';

	new_input = str_to_var_input(&head, input, new_input, nlen);

	free(input);
	free(status);
	free_variable_list(&head);

	return (new_input);
}

/**
 * str_to_var_input - replaces string into variables
 * @head: head
 * @new_input: new input str
 * @input: input string
 * @nlen: length
 * Return: string
 */
char *str_to_var_input(var_list **head, char *input, char *new_input, int nlen)
{
	var_list *indx;
	int i, j, k;

	indx = *head;
	for (j = i = 0; i < nlen; i++)
	{
		if (input[j] == '$')
		{
			if (!(indx->len_var) && !(indx->len_val))
			{
				new_input[i] = input[j];
				j++;
			}
			else if (indx->len_var && !(indx->len_val))
			{
				for (k = 0; k < indx->len_var; k++)
					j++;
				i--;
			}
			else
			{
				for (k = 0; k < indx->len_val; k++)
				{
					new_input[i] = indx->val[k];
					i++;
				}
				j += (indx->len_var);
				i--;
			}
			indx = indx->next;
		}
		else
		{
			new_input[i] = input[j];
			j++;
		}
	}

	return (new_input);
}

/**
 * variable_checker - check if input is $$ or $?
 * @h: head of the list
 * @in: input string
 * @st: last shell state
 * @arg_struct: struct
 * Return: void
 */
int variable_checker(var_list **h, char *in, char *st, arg_list *arg_struct)
{
	int i, lst, lpd;

	lst = _strlen(st);
	lpd = _strlen(arg_struct->pid);

	for (i = 0; in[i]; i++)
	{
		if (in[i] == '$')
		{
			if (in[i + 1] == '?')
				add_var_node(h, 2, st, lst), i++;
			else if (in[i + 1] == '$')
				add_var_node(h, 2, arg_struct->pid, lpd), i++;
			else if (in[i + 1] == '\n')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\0')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == ' ')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == '\t')
				add_var_node(h, 0, NULL, 0);
			else if (in[i + 1] == ';')
				add_var_node(h, 0, NULL, 0);
			else
				env_checker(h, in + i, arg_struct);
		}
	}

	return (i);
}
