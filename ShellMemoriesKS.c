#include "shell.h"

/**
 * ptr_free - it frees a pointer and makes address NULL
 * @pntr: pointer address to free
 * Return: returns 1 if freed, otherwise returns 0.
 */

int ptr_free(void **pntr)
{
	if (pntr && *pntr)
	{
		free(*pntr);
		*pntr = NULL;
		return (1);
	}
	return (0);
}
