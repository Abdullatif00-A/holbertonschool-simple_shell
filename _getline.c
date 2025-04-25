#include "shell.h"
#define READ_BUF_SIZE 128

/**
 * _getline - Custom getline function to read a line from stdin
 * @lineptr: Pointer to buffer where the line will be stored
 * @n: Pointer to size of the buffer
 * @fd: File descriptor to read from (STDIN_FILENO)
 *
 * Return: Number of characters read, or -1 on failure/EOF
 */
ssize_t _getline(char **lineptr, size_t *n, int fd)
{
	static char buffer[READ_BUF_SIZE];
	static size_t buf_pos, buf_size;
	size_t total_read = 0;
	char *new_lineptr;
	char c;
	size_t old_size;

	if (!lineptr || !n)
		return (-1);

	if (*lineptr == NULL || *n == 0)
	{
		*n = READ_BUF_SIZE;
		*lineptr = malloc(*n);
		if (!*lineptr)
			return (-1);
	}

	while (1)
	{
		if (buf_pos >= buf_size)
		{
			buf_size = read(fd, buffer, READ_BUF_SIZE);
			if (buf_size <= 0)
				return (total_read > 0 ? (ssize_t)total_read : (ssize_t)-1);
			buf_pos = 0;
		}

		c = buffer[buf_pos++];
		(*lineptr)[total_read++] = c;

		if (total_read >= *n)
		{
			old_size = *n;
			*n *= 2;
			new_lineptr = _realloc(*lineptr, old_size, *n);
			if (!new_lineptr)
				return (-1);
			*lineptr = new_lineptr;
		}

		if (c == '\n')
			break;
	}

	(*lineptr)[total_read] = '\0';
	return ((ssize_t)total_read);
}


