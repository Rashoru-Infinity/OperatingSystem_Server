#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "client.h"

int main(int argc, char **argv)
{
	int		sockfd;
	struct	sockaddr_in serv;
	char	*content;
	char	*hash_value;

	if (argc != 4)
	{
		printf("Usage %s host port keyfile\n", argv[0]);
		exit(1);
	}
	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket\n");
		exit(1);
	}
	serv.sin_family = PF_INET;
	serv.sin_port = htons(strtol(argv[2], NULL, 10));
	inet_aton(argv[1], &serv.sin_addr);
	if (connect(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
	{
		perror("connect\n");
		exit(1);
	}
	if (!(content = read_file(argv[3], 1024)))
	{
		perror("read_file\n");
		exit(1);
	}
	if (!(hash_value = atoSHA256(content)))
	{
		perror("atoSHA256\n");
		exit(1);
	}
	if (authorize(sockfd, hash_value) == fail)
	{
		perror("authorize\n");
		exit(1);
	}
	if (request(sockfd) == fail)
	{
		perror("request\n");
		exit(1);
	}
	close(sockfd);
	free(content);
	free(hash_value);
	return (0);	
}
