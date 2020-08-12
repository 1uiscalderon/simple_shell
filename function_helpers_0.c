#include "shell.h"

/**
 * _realloc - Reallocates a memory block using malloc and free.
 * @ptr: pointer to the old block of memory.
 * @old_size: .
 * @new_size: .
 * Return: Pointer to the allocated memory, NULL if fails.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p = NULL, *ptr1 = NULL;
	void *p1 = NULL;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
	{
		ptr = malloc(new_size);
		return (ptr);
	}
	else if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	ptr1 = (char *)ptr;
	if (new_size > old_size)
	{
		p = malloc(new_size);
		if (p == NULL)
			return (NULL);
		for (i = 0; i < old_size; i++)
			p[i] = ptr1[i];
	}
	else if (new_size < old_size)
	{
		p = malloc(new_size);
		if (p == NULL)
			return (NULL);
		for (i = 0; i < new_size; i++)
			p[i] = ptr1[i];
	}
	free(ptr);
	p1 = (void *)p;
	return (p1);
}

void free_pointer_array(char **token_array)
{
	int i;
	for (i = 0; token_array[i] != NULL; i++)
		free(token_array[i]);
	free(token_array);
}