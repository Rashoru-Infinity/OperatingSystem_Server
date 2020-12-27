#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

static char *get_path(char *reponame)
{
	char	*full;
	char	*home;

	home = getenv("HOME");
	if (!(full = calloc(strlen(home) * strlen(reponame) + 2, sizeof(char))))
		return (NULL);
	strcpy(full, home);
	strncat(full, "/repo/", strlen("/repo/"));
	strncat(full, reponame, strlen(reponame));
	return (full);
}

static char *get_cmd(char *path)
{
	char *cmd;
	const char	*git_init = "git init --bare ";

	if (!(cmd = calloc(strlen(path) + strlen(git_init) + 1, sizeof(char))))
		return (NULL);
	strcpy(cmd, git_init);
	strncat(cmd, path, strlen(path));
	return (cmd);
}

char	*gen_repository(char *name)
{
	char		*path;
	char		*cmd;
	struct stat	stat_buf;

	if (!(path = get_path(name)))
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
