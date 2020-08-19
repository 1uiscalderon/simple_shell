#include "shell.h"

/**
 * signal_handler - Prevents exiting when pressing ctrl + c
 * @n: Signal
 */
void signal_handler(int n)
{
	if (n == SIGINT)
		write(STDOUT_FILENO, "\n$ ", 3);
}

/**
 * _strlen - Returns the lenght of a string
 * @s: pointer to string
 * Return: Lenght of string, excluding NULL character
 */

int _strlen(char *s)
{
	int i;

	for (i = 0; s[i] != '\0'; i++)
		;
	return (i);
}

/**
 *_calloc - Mimics calloc function using malloc.
 *@nmemb: number of elements of the allocated memory block.
 *@size: size of each element of the block.
 *Return: Pointer to the allocated memory, NULL if fails.
 */

void *_calloc(unsigned int nmemb, unsigned int size)
{
	void *p;
	char *ptr;
	unsigned int i, block_size;

	if (nmemb == 0 || size == 0)
		return (NULL);

	p = malloc(nmemb * size);
	if (p == NULL)
		return (p);

	block_size = nmemb * size;
	ptr = p;
	for (i = 0; i < block_size; i++)
		ptr[i] = 0;

	return (p);
}

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
		p = malloc(new_size); /*ES NECESARIO LIBERAR ptr?*/
		if (p == NULL)
			return (NULL);
		for (i = 0; i < new_size; i++)
			p[i] = ptr1[i];
	}
	free(ptr);
	p1 = (void *)p;
	return (p1);
}

/**
 * free_pointer_array - Free all pointers in an Array of strings
 * @token_array: Array of pointers
 */
void free_pointer_array(char **token_array)
{
	int i;

	if (token_array == NULL)
		return;

	for (i = 0; token_array[i] != NULL; i++)
		free(token_array[i]);
	free(token_array);
}
