#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "server.h"

static char *get_path(const char *home, const char *reponame)
{
	char	*full;

	if (!(full = strargcat(5, home, "/repo", "/", reponame, ".git")))
		return (NULL);
	return (full);
}

static char *get_cmd(const char *path)
{
	char *cmd;
	const char	*git_init = "git init --bare ";

	if (!(cmd = calloc(strlen(path) + strlen(git_init) + 1, sizeof(char))))
		return (NULL);
	strcpy(cmd, git_init);
	strncat(cmd, path, strlen(path));
	return (cmd);
}

char	*gen_repository(const char *home, const char *name)
{
	char		*path;
	char		*cmd;
	struct stat	stat_buf;

	if (!(path = get_path(home, name)))
		return (NULL);
	if (!stat(path, &stat_buf))
	{
		free(path);
		return (NULL);
	}
	if (mkdir(path, 0755))
	{
		free(path);
		return (NULL);
	}
	if (!(cmd = get_cmd(path)))
	{
		free(path);
		return (NULL);
	}
	if (system(cmd) < 0)
	{
		free(path);
		free(cmd);
		return (NULL);
	}
	free(cmd);
	return (path);
}
