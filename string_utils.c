#include "shell.h"
#include <stdlib.h>

/**
 * _strcmp - Compare two strings
 * @s1: First string
 * @s2: Second string
 * Return: 0 if equal, negative or positive if different
 */
int _strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

/**
 * _strdup - Duplicate a string
 * @s: String to duplicate
 * Return: Pointer to new string, or NULL if failed
 */
char *_strdup(const char *s)
{
	char *dup;
	size_t len = 0, i;

	while (s[len])
		len++;

	dup = malloc(len + 1);
	if (!dup)
		return (NULL);

	for (i = 0; i < len; i++)
		dup[i] = s[i];
	dup[len] = '\0';

	return (dup);
}

/**
 * _strchr - Locate first occurrence of character c in string s
 * @s: The string
 * @c: The character to find
 * Return: Pointer to first occurrence, or NULL if not found
 */
char *_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	return (c == '\0' ? (char *)s : NULL);
}

/**
 * _realloc - Custom realloc implementation
 * @ptr: Pointer to the previously allocated memory
 * @old_size: Size of the old memory block
 * @new_size: Size of the new memory block
 *
 * Return: Pointer to the new memory block, or NULL if it fails
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *new_ptr;
	unsigned int i;

	if (new_size == old_size)
		return (ptr);

	if (ptr == NULL)
	{
		new_ptr = malloc(new_size);
		if (new_ptr == NULL)
			return (NULL);
		return (new_ptr);
	}

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}

	new_ptr = malloc(new_size);
	if (new_ptr == NULL)
		return (NULL);

	for (i = 0; i < old_size && i < new_size; i++)
		new_ptr[i] = ((char *)ptr)[i];

	free(ptr);
	return (new_ptr);
}

