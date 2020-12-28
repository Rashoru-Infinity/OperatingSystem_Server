CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= srcs/main.c srcs/request.c srcs/send_hash.c
OBJS	= $(SRCS:.c=.o)
INCLUDES	= -Iincludes -I$(MD5)/includes -I$(READFILE)/includes
MD5	= ../lib/md5
READFILE	= ../lib/read_file
LINK	= -L ../lib/read_file/ -lreadfile -L ../lib/md5 -latomd5 -lcrypto
NAME	= git_client
RM	= rm -f

all	:	$(NAME)

.c.o	:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME)	:	$(OBJS)
	$(MAKE) -C ../lib/md5 all
	$(MAKE) -C ../lib/read_file all
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LINK)

clean	:
	$(MAKE) -C ../lib/md5 clean
	$(MAKE) -C ../lib/read_file clean
	$(RM) $(OBJS)

fclean	:	clean
	$(MAKE) -C ../lib/md5 fclean
	$(MAKE) -C ../lib/read_file fclean
	$(RM) $(NAME)

re	:	fclean	all

.PHONY	:	all clean fclean re	
