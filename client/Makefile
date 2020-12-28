CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= srcs/main.c srcs/request.c srcs/send_hash.c
OBJS	= $(SRCS:.c=.o)
INCLUDES	= -Iincludes -I$(SHA256)/includes -I$(READFILE)/includes -I$(LIBTYPE)/includes
SHA256	= ../lib/sha256
READFILE	= ../lib/read_file
LIBTYPE	=	../lib
LINK	= -L ../lib/read_file/ -lreadfile -L ../lib/sha256 -latoSHA256 -lcrypto
NAME	= git_client
RM	= rm -f

all	:	$(NAME)

.c.o	:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME)	:	$(OBJS)
	$(MAKE) -C ../lib/sha256 all
	$(MAKE) -C ../lib/read_file all
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LINK)

clean	:
	$(MAKE) -C ../lib/sha256 clean
	$(MAKE) -C ../lib/read_file clean
	$(RM) $(OBJS)

fclean	:	clean
	$(MAKE) -C ../lib/sha256 fclean
	$(MAKE) -C ../lib/read_file fclean
	$(RM) $(NAME)

re	:	fclean	all

.PHONY	:	all clean fclean re	
