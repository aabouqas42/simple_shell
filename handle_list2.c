#include "shell.h"

/**
 * free_variable_list - frees list
 * @head: list's head
 * Return: void
 */
void free_variable_list(var_list **head)
{
	var_list *temp;
	var_list *curr;

	if (head != NULL)
	{
		curr = *head;
		while ((temp = curr) != NULL)
		{
			curr = curr->next;
			free(temp);
		}
		*head = NULL;
	}
}

/**
 * add_var_node - adds var to the end of a list
 * @head: list's head
 * @lvar: variable length
 * @val: variable value
 * @lval: value length
 * Return: pointer to head
 */
var_list *add_var_node(var_list **head, int lvar, char *val, int lval)
{
	var_list *new, *temp;

	new = malloc(sizeof(var_list));
	if (new == NULL)
		return (NULL);

	new->len_var = lvar;
	new->val = val;
	new->len_val = lval;

	new->next = NULL;
	temp = *head;

	if (temp == NULL)
	{
		*head = new;
	}
	else
	{
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}

	return (*head);
}
