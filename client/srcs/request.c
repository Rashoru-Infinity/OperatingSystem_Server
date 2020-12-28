#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int request(int sockfd)
{
	char *buf;
	const int DEFAULT_SIZE = 256;

	if (!(buf = calloc(DEFAULT_SIZE + 1, sizeof(char))))
		return (-1);
	printf(">");
	while (fgets(buf, DEFAULT_SIZE + 1, stdin))
	{
		if (strcmp("exit\n", buf) == 0)
		{
			free(buf);
			break;
		}
		if (send(sockfd, buf, DEFAULT_SIZE + 1, 0) < 0)
		{
			free(buf);
			return (-1);
		}
		bzero(buf, DEFAULT_SIZE + 1);
		if (recv(sockfd, buf, DEFAULT_SIZE + 1, 0) < 0)
		{
			free(buf);
			return (-1);
		}
		printf("%s\n", buf);
		bzero(buf, DEFAULT_SIZE + 1);
		printf(">");
	}
	return (0);
}
