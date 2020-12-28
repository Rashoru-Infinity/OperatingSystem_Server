#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int request(int sockfd)
{
	char		*buf;
	char		*line_break;
	const int	DEFAULT_SIZE = 256;

	if (!(buf = calloc(DEFAULT_SIZE + 1, sizeof(char))))
		return (-1);
	printf(">");
	while (fgets(buf, DEFAULT_SIZE + 1, stdin))
	{
		if ((line_break = strrchr(buf, '\n')))
			*line_break = '\0';
		if (send(sockfd, buf, DEFAULT_SIZE + 1, 0) < 0)
		{
			free(buf);
			return (-1);
		}
		if (strcmp("exit", buf) == 0)
		{
			printf("exit\n");
			free(buf);
			break;
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
