#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include "client.h"

t_status	authorize(int sockfd, const char *hash)
{
	int			status;
	char		*msg;
	const int	DEFAULT_SIZE = 256;

	if(!(msg = calloc(DEFAULT_SIZE + 1, sizeof(char))))
		return (fail);
	strcpy(msg, hash);
	if ((status = send(sockfd, msg, DEFAULT_SIZE + 1, 0)) < 0)
	{
		free(msg);
		return (fail);
	}
	bzero(msg, DEFAULT_SIZE + 1);
	if ((status = recv(sockfd, msg, DEFAULT_SIZE + 1, 0)) < 0)
	{
		free(msg);
		return (fail);
	}
	if (strcmp(msg, "success") != 0)
	{
		free(msg);
		return (fail);
	}
	free(msg);
	return (success);
}
