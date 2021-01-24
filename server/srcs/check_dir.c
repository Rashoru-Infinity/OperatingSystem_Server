#include "server.h"
#include <dirent.h>

t_status	check_dir(t_hash *file_list, const char *path)
{
	DIR				*dir;
	struct dirent	*dp;

	if (!file_list || !path)
		return (fail);
	if (!(dir = opendir(path)))
		return (fail);
	dp = readdir(dir);
	while (dp)
	{
		if (hash_add(file_list, dp->d_name) == fail)
		{
			closedir(dir);
			return (fail);
		}
		dp = readdir(dir);
	}
	closedir(dir);
	return (success);
}
