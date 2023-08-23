#include "shell.h"

/**
 * _realloc - custom realloc function
 * @ptr: ptr to prev memory
 * @old_size: size of the allocated mem
 * @new_size: size of the new memory mem
 * Return: ptr
 *	if new_size == old_size ret ptr
 *	if malloc fails, returns NULL
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *newptr;

	if (ptr == NULL)
		return (malloc(new_size));

	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(new_size);
	if (newptr == NULL)
		return (NULL);

	if (new_size < old_size)
		ptr_memcpy(newptr, ptr, new_size);
	else
		ptr_memcpy(newptr, ptr, old_size);

	free(ptr);
	return (newptr);
}

/**
 * ptr_memcpy - copies pointer data
 * @newptr: dest ptr
 * @ptr: source ptr
 * @size: size of new ptr
 * Return: void
 */
void ptr_memcpy(void *newptr, const void *ptr, unsigned int size)
{
	char *char_ptr = (char *)ptr;
	char *char_newptr = (char *)newptr;
	unsigned int i;

	for (i = 0; i < size; i++)
		char_newptr[i] = char_ptr[i];
}

/**
 * _realloc_dup - reallocates a memory block of a double ptr
 * @ptr: double ptr to prev memory
 * @old_size: size of the allocated mem
 * @new_size: size of the new memory mem
 * Return: ptr
 *	if new_size == old_size ret ptr
 *	if malloc fails, returns NULL
 */
char **_realloc_dup(char **ptr, unsigned int old_size, unsigned int new_size)
{
	char **newptr;
	unsigned int i;

	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size));

	if (new_size == old_size)
		return (ptr);

	newptr = malloc(sizeof(char *) * new_size);
	if (newptr == NULL)
		return (NULL);

	for (i = 0; i < old_size; i++)
		newptr[i] = ptr[i];

	free(ptr);

	return (newptr);
}
