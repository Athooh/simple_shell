#include "shell.h"

/**
 * memory_set - it updates memory with a constant byte
 * @m: memory area pointer
 * @b: byte to filled with *m
 * @n: bytes amount to be filled
 * Return: returns (m) a pointer to the m memory area
 */

char *memory_set(char *m, char b, unsigned int n)
{
	unsigned int xs;

	for (xs = 0; xs < n; xs++)
		m[xs] = b;
	return (m);
}

/**
 * str_free - it frees string of strings
 * @s: string of strings
 */

void str_free(char **s)
{
	char **as = s;

	if (!s)
		return;
	while (*s)
		free(*s++);
	free(as);
}

/**
 * mem_realloc - it reallocates the memory block
 * @ptr: previous malloc'ated block pointer
 * @ol_size: previous block byte size
 * @nw_size: new block byte size
 * Return: returns old'block nameen pointer.
 */

void *mem_realloc(void *ptr, unsigned int ol_size, unsigned int nw_size)
{
	char *ss;

	if (!ptr)
		return (malloc(nw_size));
	if (!nw_size)
		return (free(ptr), NULL);
	if (nw_size == ol_size)
		return (ptr);

	ss = malloc(nw_size);
	if (!ss)
		return (NULL);

	ol_size = ol_size < nw_size ? ol_size : nw_size;
	while (ol_size--)
		ss[ol_size] = ((char *)ptr)[ol_size];
	free(ptr);
	return (ss);
}
