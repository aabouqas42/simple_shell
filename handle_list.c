#include "shell.h"

/**
 * free_list_string - frees the list
 * @head: list's head
 * Return: void
 */
void free_list_string(list_string **head)
{
	list_string *curr;
	list_string *temp;

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
 * free_seperator - frees sep list
 * @head: list's head
 * Return: void
 */
void free_seperator(separator_list **head)
{
	separator_list *curr;
	separator_list *temp;

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
 * line_node - adds cmd line at the end
 * @head: list's head
 * @line: cmd line
 * Return: pointer to head
 */
list_string *line_node(list_string **head, char *line)
{
	list_string *new, *temp;

	new = malloc(sizeof(list_string));
	if (new == NULL)
		return (NULL);

	new->line = line;
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

/**
 * separator_node - adds separator to head
 * @head: head
 * @sep: separator
 * Return: pointer to head
 */
separator_list *separator_node(separator_list **head, char sep)
{
	separator_list *new, *temp;

	new = malloc(sizeof(separator_list));
	if (new == NULL)
		return (NULL);

	new->separator = sep;
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
