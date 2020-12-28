#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include "read_file.h"
#include "md5.h"

int	identify(const char *hash)
{
	char			*home;
	const char		*keyfile = "authorizedkey";
	char			*full;
	struct stat		stat_buf;
	char			*content;
	char			*content_hash;
	const size_t	DEFAULT_SIZE = 2048;

	if (!hash)
		return (-1);
	home = getenv("HOME");
	if (!(full = calloc(strlen(home) + strlen(keyfile) + 2, sizeof(char))))
		return (-1);
	strcpy(full, home);
	strncat(full, "/", strlen("/"));
	strncat(full, keyfile, strlen(keyfile));
	if (stat(full, &stat_buf))
	{
		free(full);
		return (-1);
	}
	if (!(content = read_file(full, DEFAULT_SIZE)))
	{
		free(full);
		return (-1);
	}
	if (!(content_hash = atomd5(content)))
	{
		free(full);
		free(content);
		return (-1);
	}
	if (strcmp(hash, content_hash) != 0)
	{
		free(full);
		free(content);
		free(content_hash);
		return (-1);
	}
	free(full);
	free(content);
	free(content_hash);
	return (0);
}
