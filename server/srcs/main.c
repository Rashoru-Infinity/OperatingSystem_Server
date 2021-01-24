#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "server.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <pthread.h>

typedef struct	s_update {
	int		*pipefd;
	t_hash	*name_list;
	char	*buf;
	int		buf_size;
	int		new_sockfd;
}				t_update;

typedef struct	s_upload {
	int			*pipefd;
	char		*buf;
	int			buf_size;
	int			new_sockfd;
	char		*home;
	t_hash		*name_list;
}				t_upload;

typedef struct	s_accept {
	int					*new_sockfd;
	int					sockfd;
	struct sockaddr_in	*clnt;
	socklen_t			*sin_siz;
}				t_accept;

void send_dir(const char *home, char *buf, int buf_size, int new_sockfd, t_hash *namelist)
{
	char	*full;
	size_t	file_count;
	size_t	index;

	if (!home || !buf || !namelist || !(full = strargcat(2, home, "/repo")))
		exit(1);
	if (check_dir(namelist, full) == fail)
		exit(1);
	file_count = hash_size(*namelist);
	bzero(buf, buf_size + 1);
	memcpy(buf, &file_count, sizeof(size_t));
	if (send(new_sockfd, buf, buf_size + 1, 0) < 0)
		exit(1);
	index = 0;
	bzero(buf, buf_size + 1);
	while (index < namelist->vla.real_size)
	{
		if (namelist->vla.contents[index])
		{
			strcpy(buf, namelist.vla.contents[index]);
			if (send(new_sockfd, buf, buf_size + 1, 0) < 0)
				exit(1);
		}
	}
	free(full);
}

void authorize(char *buf, int buf_size, int new_sockfd, const char *home)
{	
	bzero(buf, buf_size + 1);
	if (recv(new_sockfd, buf, buf_size + 1, 0) < 0)
	{
		perror("recv\n");
		exit(1);
	}
	buf[buf_size] = '\0';
	if (admit(home, buf) == fail)
	{
		bzero(buf, buf_size + 1);
		strcpy(buf, "fail");
		send(new_sockfd, buf, buf_size + 1, 0);
		exit(0);
	}
	bzero(buf, buf_size + 1);
	strcpy(buf, "success");
	if (send(new_sockfd, buf, buf_size + 1, 0) < 0)
		exit(1);
}

void accept_wrapper(void *arg)
{
	t_accept	args;

	if (!arg)
		return ;
	args = (t_accept *)arg;
	if (!args->new_sockfd || !args->clnt || !args->sin_siz)
		return ;
	*(args->new_sockfd)
	= accept(args->sockfd, (struct sockaddr *)&args->clnt, args->sin_siz);
}

void reflect_change(void *arg)
{
	t_update	*args;
	size_t		list_size;

	if (!arg)
		return ;
	args = (t_update *)arg;
	if (!args->name_list || args->name_list->vla.real_size == 0 || !args->buf)
		return ;
	list_size = hash_size(*(args->name_list));
	bzero(args->buf, args->buf_size + 1);
	if (read(pipefd[0], args->buf, args->buf_size) < 0)
		return ;
	write(pipefd[1], args->buf, args->buf_size);
	hash_add(args->name_list, args->buf);
}

void update_dir(void *arg)
{
	t_update	*args;
	size_t		list_size;

	if (!arg)
		return ;
	args = (t_update *)arg;
	if (!args->name_list || args->name_list->vla.real_size == 0 || !args->buf)
		return ;
	list_size = hash_size(*(args->name_list));
	bzero(args->buf, args->buf_size + 1);
	while (read(pipefd[0], args->buf, args->buf_size) > 0)
	{
		if (hash_add(args->name_list, args->buf) == fail)
			return ;
		if (list_size != hash_size(*(args->name_list)))
		{
			if (send(args->new_sockfd, args->buf, args->buf_size + 1, 0) < 0)
				exit(1);
			list_sizse = hash_size(*(args->name_list));
		}
		bzero(args->buf, args->buf_size + 1);
	}
}

void upload_dir(void *arg)
{
	t_upload	*args;
	char		*repodir;
	char		*fullpath;

	if (!arg)
		return ;
	args = arg;
	if (!args->buf || !args->home || !args->name_list || !args->pipefd)
		return ;
	bzero(args->buf, args->buf_size + 1);
	while (recv(args->new_sockfd, args->buf, args->buf_size + 1, 0) > 0)
	{
		repodir = NULL;
		fullpath = NULL;
		args->buf[args->buf_size] = '\0';
		if (strcmp(args->buf, "exit") == 0)
			exit(0);
		if (is_safestr(args->buf))
		{
			if (!(fullpath = strargcat(4, args->home, "/repo/", args->buf, ".git")))
				return ;
			if (!hash_contains(args->name_list, fullpath))
			{
				repodir = gen_repository(args->home, args->buf);
				bzero(args->buf, args->buf_size + 1);
				if (repodir)
				{
					write(pipefd[1], fullpath, strlen(fullpath));
					hash_add(args->name_list, fullpath);
					fullpath = NULL;
					strcpy(args->buf, repodir);
					if (send(args->new_sockfd, args->buf, args->buf_size + 1, 0) < 0)
						exit(1);
					bzero(args->buf, args->buf_size + 1);
					free(repodir);
					continue ;
				}
			}
		}
		strcpy(args->buf, "fail to generate repository");
		if (send(args->new_sockfd, args->buf, args->buf_size + 1, 0) < 0)
			exit(1);
		free(repodir);
		free(fullpath);
	}
}

void	main_communication(char *buf, int buf_size, int new_sockfd,
		char *home, t_hash *namelist, int *pipefd)
{
	t_update	update;
	t_upload	upload;
	pthread_t	update_th;
	pthread_t	upload_th;

	update = (t_update){pipefd, name_list, buf, buf_size};
	upload = (t_upload){pipefd, buf, buf_size, new_sockfd, home, name_list};
	if (pthread_create(&update_th, NULL, (void *)update_dir, (void *)&update))
	{
		perror("pthread_create\n");
		exit(1);
	}
	if (pthread_create(&upload_th, NULL, (void *)upload_dir, (void *)&upload))
	{
		perror("pthread_create\n");
		exit(1);
	}
	if (pthread_join(update_th, NULL))
	{
		perror("pthread_join\n");
		exit(1);
	}
	if (pthread_join(upload_th, NULL))
	{
		perror("pthread_join\n");
		exit(1);
	}
}

int main(int argc, char **argv)
{
	int					sockfd, new_sockfd;
	char				*buf;
	const int			DEFAULT_SIZE = 256;
	struct sockaddr_in	serv, clnt;
	socklen_t			sin_siz;
	char				*home;
	pid_t				pid;
	int					status;
	t_hash				name_list;
	int					pipefd[2];
	t_accept			accept_args;
	pthread_t			accept_wrapper_th;
	pthread_t			reflect_change_th;

	if (argc != 2)
	{
		printf("Usage: %s port\n", argv[0]);
		exit(1);
	}
	if (!(buf = malloc(sizeof(char) * (DEFAULT_SIZE + 1))))
	{
		perror("malloc\n");
		exit(1);
	}
	if (hash_init(&name_list, 10, NULL, hash_func, is_same) == fail)
	{
		perror("hash_init");
		exit(1);
	}
	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("socket\n");
		exit(1);
	}
	bzero(&serv, sizeof(struct sockaddr_in));
	serv.sin_family = PF_INET;
	serv.sin_port = htons(strtol(argv[1], NULL, 10));
	serv.sin_addr.s_addr = htonl(INADDR_ANY);
	sin_siz = sizeof(struct sockaddr_in);
	if (bind(sockfd, (struct sockaddr *)&serv, sizeof(serv)) < 0)
	{
		perror("bind\n");
		exit(1);
	}
	if (listen(sockfd, SOMAXCONN) < 0)
	{
		perror("listen\n");
		exit(1);
	}
	accept_args = (t_accept){&new_sockfd, sockfd, &clnt, &sin_siz};
	home = getenv("HOME");
	if (daemon(0, 0) != 0)
	{
		perror("daemon\n");
		exit(1);
	}
	if (pipe(pipefd) == -1)
	{
		perror("pipe\n");
		exit(1);
	}
	if (pthread_cread(&reflect_change_th, NULL, (void *)reflect_change, (void *)&accept_args))
	{
		perror("pthread_create\n");
		exit(1);
	}
	while (1)
	{
		if (pthread_cread(&accept_wrapper_th, NULL, (void *)reflect_change, (void *)&accept_args))
		{
			perror("pthread_create\n");
			exit(1);
		}
		if ((new_sockfd = accept(sockfd, (struct sockaddr *)&clnt, &sin_siz)) < 0)
			perror("accept\n");
		switch((pid = fork()))
		{
		case 0:
			switch(fork())
			{
			case 0:
				authorize(buf, size, new_sockfd, home);
				send_dir(home, buf, DEFAULT_SIZE, new_sockfd, name_list);
				main_communication(buf, buf_size, new_sockfd, home);
				exit(0);
			case -1:
				exit(1);
			default:
				exit(0);
			}
		case -1:
			exit(1);
		default:
			waitpid(pid, &status, 0);
		}
		close(new_sockfd);
	}
	close(sockfd);
	close(pipefd[0]);
	close(pipefd[1]);
	hash_clear(&name_list, false, true);
	return (0);
}
