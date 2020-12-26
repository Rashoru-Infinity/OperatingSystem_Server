#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int request(int sockfd)
{
	char *buf;
	const int DEFAULT_SIZE = 64;

	if (!(buf = malloc(sizeof(char) * (DEFAULT_SIZE + 1))))
		return (-1);
	printf(">");
	while (fgets(buf, DEFAULT_SIZE + 1, stdin))
	{
		if (strcmp("exit\n", buf) == 0)
		{
			free(buf);
			break;
		}
		if (send(sockfd, buf, strlen(buf), 0) < 0)
		{
			free(buf);
			return (-1);
		}
		printf(">");
	}
	return (0);
}
