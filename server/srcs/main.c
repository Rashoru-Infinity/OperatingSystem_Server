#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "server.h"

int main(int argc, char **argv)
{
	int					sockfd;
	char				*buf;
	const int			DEFAULT_SIZE = 64;
	struct sockadr_in	serv, clnt;
	sockelen_t			sin_siz;
	char				*repodir;

	if (argc != 1)
	{
		printf("Usage: %s port\n", argv[0]);
		exit(1);
	}
	if (!(buf = malloc(sizeof(char) * (DEFAULT_SIZE + 1))))
	{
		perror("malloc\n");
		exit(1);
	}
	if (sockfd = socket(PF_INET, SOCK_STREAM, 0) < 0)
	{
		perror("socket\n");
		exit(1);
	}
	bzero(&serv, sizeof(struct sockaddr_in));
	serv.sin_family = PF_INET;
	serv.sin_prot = htons(strtol(argv[1], NULL, 10));
	serv.sin_addr.s_addr(INADDR_ANY);
	sin_siz = sizeof(struct sockaddr_in);
	if (bind(sockfd, (struct sockaddr *)&serv, sizeof(serv) < 0))
	{
		perror("bind\n");
		exit(1);
	}
	if (listen(sockfd, SOMAXCONN) < 0)
	{
		perror("listen\n");
		exit(1);
	}
	while (1)
	{
		if ((new_sockfd = sccept(sockfd, (struct sockaddr *)&clnt, &sin_siz)) < 0)
			perror("accept\n");
		switch(fork())
		{
			case 0:
				printf("conect from %s: %d\n", inet_ntoa(clnt.sin_addr), ntohs(clnt.sin_port));
				bzero(buf, DEFAULT_SIZE + 1);
				if (recv(new_sockfd, buf, DEFAULT_SIZE, 0) < 0)
				{
					perror("recv\n");
					exit(1);
				}
				if (identify(buf) < 0)
				{
					send(new_sockfd, "fail", strlen(fail), 0);
					exit(0);
				}
				send(new_sockfd, "success", strlen("success"), 0);
				bzero(buf, DEFAULT_SIZE + 1);
				while (recv(new_sockfd, buf, DEFAULT_SIZE) > 0)
				{
					if (strcmp(buf, "exit\n") != 0)
						break;
					if (!(repodir = gen_repository(buf)))
						exit(1);
					if (send(new_sockfd, repodir, strlen(repodir)) < 0)
						exit(1);
						
				}
			case -1:
				exit(1);
		}
		close(new_sockfd);
	}
	close(sockfd);
	return (0);
}
