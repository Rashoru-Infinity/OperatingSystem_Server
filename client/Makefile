CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= srcs/main.c srcs/request.c
OBJS	= $(SRCS:.c=.o)
INCLUDES	= -Iincludes
LINK	= -L srcs/read_file/ -lreadfile -L srcs/md5 -latomd5 -L srcs/auth -lauth -lcrypto
NAME	= git_client
RM	= rm -f

all	:	$(NAME)

.c.o	:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME)	:	$(OBJS)
	$(MAKE) -C srcs/auth all
	$(MAKE) -C srcs/md5 all
	$(MAKE) -C srcs/read_file all
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LINK)

clean	:
	$(MAKE) -C srcs/auth clean
	$(MAKE) -C srcs/md5 clean
	$(MAKE) -C srcs/read_file clean
	$(RM) $(OBJS)

fclean	:	clean
	$(MAKE) -C srcs/auth fclean
	$(MAKE) -C srcs/md5 fclean
	$(MAKE) -C srcs/read_file fclean
	$(RM) $(NAME)

re	:	fclean	all

.PHONY	:	all clean fclean re	
