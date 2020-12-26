#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>

int	send_hash(int sockfd, const char *hash)
{
	int		status;
	char	*msg;

	if(!(msg = malloc((strlen("success") + 1) * sizeof(char))))
		return (-1);
	if ((status = send(sockfd, hash, strlen(hash), 0)) < 0)
		return (status);
	if ((status = recv(sockfd, msg, strlen("success"), 0)) < 0)
	{
		free(msg);
		return (-1);
	}
	msg[status] = '\0';
	if (strcmp(msg, "success") != 0)
	{
		free(msg);
		return (-1);
	}
	return (status);
}
