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
	unsigned int x;

	for (x = 0; x < n; x++)
		m[x] = b;
	return (m);
}

/**
 * str_free - it frees string of strings
 * @s: string of strings
 */

void str_free(char **s)
{
	char **a = s;

	if (!s)
		return;
	while (*s)
		free(*s++);
	free(a);
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
	char *s;

	if (!ptr)
		return (malloc(nw_size));
	if (!nw_size)
		return (free(ptr), NULL);
	if (nw_size == ol_size)
		return (ptr);

	s = malloc(nw_size);
	if (!s)
		return (NULL);

	ol_size = ol_size < nw_size ? ol_size : nw_size;
	while (ol_size--)
		s[ol_size] = ((char *)ptr)[ol_size];
	free(ptr);
	return (s);
}
