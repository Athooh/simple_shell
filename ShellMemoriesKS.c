#include "shell.h"

/**
 * ptr_free - it frees a pointer and makes address NULL
 * @ptr: pointer address to free
 * Return: returns 1 if freed, otherwise returns 0.
 */

int ptr_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
