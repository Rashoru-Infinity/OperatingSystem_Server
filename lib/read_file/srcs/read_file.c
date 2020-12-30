#include <stdlib.h>
#include "read_file.h"
#include <string.h>
#include <stdint.h>
#include <stdio.h>
#include <errno.h>

static size_t strlen_eof(const char *s)
{
	size_t len;

	len = 0;
	while (*s != 0x1a)
	{
		++len;
		++s;
	}
	return (len);
}

static t_status append_buf(char **s, char *buf, size_t *curr_size, size_t *max_size)
{
	char *tmp;

	if (!s || !*s || !buf || !max_size)
		return (fail);
	if (*max_size > SIZE_MAX - 1 || SIZE_MAX - *curr_size < strlen_eof(buf))
		return (fail);
	while (*curr_size + strlen_eof(buf) > *max_size + 1)
	{
		if (*max_size > (SIZE_MAX - 1) / 2)
			return (fail);
		tmp = realloc(*s, *max_size * 2);
		if (!tmp)
			return (fail);
		*s = tmp;
		*max_size *= 2;
	}
	memcpy(&(*s)[*curr_size], buf, strlen_eof(buf));
	*curr_size += strlen_eof(buf);
	(*s)[*curr_size] = '\0';
	return (success);
}

char	*read_file(const char *file_name, size_t buffer_size)
{
	FILE			*fp;
	char			*data;
	char			*buf;
	const size_t	DEFAULT_SIZE = 2048;
	size_t			read_size;
	size_t			curr_size;
	size_t			max_size;

	curr_size = 0;
	max_size = DEFAULT_SIZE;
	if (buffer_size == SIZE_MAX)
		return (NULL);
	if (!(fp = fopen(file_name, "r")))
	{
		perror(strerror(errno));
		return (NULL);
	}
	if (!(buf = malloc(sizeof(char) * (buffer_size + 1))))
	{
		fclose(fp);
		return (NULL);
	}
	if (!(data = malloc(sizeof(char) * (DEFAULT_SIZE + 1))))
	{
		free(buf);
		fclose(fp);
		return (NULL);
	}
	while (!feof(fp))
	{
		read_size = fread(buf, sizeof(char), buffer_size, fp);
		buf[read_size] = 0x1a;
		if (ferror(fp))
		{
			free(buf);
			free(data);
			fclose(fp);
			return (NULL);
		}
		if (append_buf(&data, buf, &curr_size, &max_size) == fail)
		{
			free(buf);
			free(data);
			fclose(fp);
			return (NULL);
		}
	}
	free(buf);
	fclose(fp);
	return (data);
}
