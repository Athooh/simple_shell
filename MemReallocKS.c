#include "shell.h"

/**
 * memory_set - it updates memory with a constant byte
 * @ms: memory area pointer
 * @bs: byte to filled with *m
 * @ns: bytes amount to be filled
 * Return: returns (m) a pointer to the m memory area
 */

char *memory_set(char *ms, char bs, unsigned int ns)
{
	unsigned int xs;

	for (xs = 0; xs < ns; xs++)
		ms[xs] = bs;
	return (ms);
}

/**
 * str_free - it frees string of strings
 * @ss: string of strings
 */

void str_free(char **ss)
{
	char **as = ss;

	if (!ss)
		return;
	while (*ss)
		free(*ss++);
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
