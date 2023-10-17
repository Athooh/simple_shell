#include "shell.h"

/**
 * print_list_str - it prints only the str element of a list_t linked list
 * @n: the pointer to first node
 * Return: returns size of list
 */

size_t print_list_str(const list_t *n)
{
	size_t x = 0;

	while (n)
	{
		_puts(n->str ? n->str : "(nil)");
		_puts("\n");
		n = n->next;
		x++;
	}
	return (x);
}

/**
 * add_node - it adds a node to start of list
 * @hd: the address of pointer to head node
 * @str: the str field of node
 * @numb: the node index used by history
 * Return: returns size of list
 */

list_t *add_node(list_t **hd, const char *str, int numb)
{
	list_t *new_head;

	if (!hd)
		return (NULL);
	new_head = malloc(sizeof(list_t));
	if (!new_head)
		return (NULL);
	memory_set((void *)new_head, 0, sizeof(list_t));
	new_head->numb = numb;
	if (str)
	{
		new_head->str = str_dup(str);
		if (!new_head->str)
		{
			free(new_head);
			return (NULL);
		}
	}
	new_head->next = *hd;
	*hd = new_head;
	return (new_head);
}

/**
 * free_list - it frees all nodes of the list
 * @hd_ptr: the head node pointer address
 * Return: returns void
 */

void free_list(list_t **hd_ptr)
{
	list_t *node, *next_node, *hd;

	if (!hd_ptr || !*hd_ptr)
		return;
	hd = *hd_ptr;
	node = hd;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*hd_ptr = NULL;
}

/**
 * add_node_end - it adds a node to the end of the list
 * @hd: the address of pointer to head node
 * @str: the str field of node
 * @numb: the node index used by history
 * Return: returns size of list
 */

list_t *add_node_end(list_t **hd, const char *str, int numb)
{
	list_t *new_node, *node;

	if (!hd)
		return (NULL);

	node = *hd;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	memory_set((void *)new_node, 0, sizeof(list_t));
	new_node->numb = numb;
	if (str)
	{
		new_node->str = str_dup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*hd = new_node;
	return (new_node);
}

/**
 * delete_node_at_index - it deletes node at given index
 * @hd: the first node pointer address
 * @idx: the index of node to delete
 * Return: returns 1 on success, returns 0 on failure
 */

int delete_node_at_index(list_t **hd, unsigned int idx)
{
	list_t *node, *prev_node;
	unsigned int x = 0;

	if (!hd || !*hd)
		return (0);

	if (!idx)
	{
		node = *hd;
		*hd = (*hd)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *hd;
	while (node)
	{
		if (x == idx)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		x++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}
