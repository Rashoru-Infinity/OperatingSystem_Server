#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include "server.h"

t_status	admit(const char *hash)
{
	char			*home;
	const char		*keyfile = "authorizedkey";
	char			*full;
	struct stat		stat_buf;
	char			*content;
	char			*content_hash;
	const size_t	DEFAULT_SIZE = 2048;

	if (!hash)
		return (fail);
	home = getenv("HOME");
	if (!(full = strargcat(3, home, "/", keyfile)))
		return (fail);
	if (stat(full, &stat_buf))
	{
		free(full);
		return (fail);
	}
	if (!(content = read_file(full, DEFAULT_SIZE)))
	{
		free(full);
		return (fail);
	}
	if (!(content_hash = atoSHA256(content)))
	{
		free(full);
		free(content);
		return (fail);
	}
	if (strcmp(hash, content_hash) != 0)
	{
		free(full);
		free(content);
		free(content_hash);
		return (fail);
	}
	free(full);
	free(content);
	free(content_hash);
	return (success);
}
