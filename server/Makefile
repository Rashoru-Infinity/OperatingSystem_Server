CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= srcs/main.c srcs/admit.c srcs/gen_repository.c
OBJS	= $(SRCS:.c=.o)
INCLUDES	= -Iincludes -I$(SHA256)/includes -I$(READFILE)/includes -I$(STRUTILS)/includes -I$(LIBTYPES)/includes
SHA256	= ../lib/sha256
READFILE	= ../lib/read_file
STRUTILS	= ../lib/strutils
LIBTYPES	= ../lib
LINK	= -L ../lib/read_file/ -lreadfile -L ../lib/sha256 -latoSHA256 -L ../lib/strutils -lstrutils -lcrypto
NAME	= git_server
RM	= rm -f

all	:	$(NAME)

.c.o	:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME)	:	$(OBJS)
	$(MAKE) -C ../lib/sha256 all
	$(MAKE) -C ../lib/read_file all
	$(MAKE) -C ../lib/strutils all
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LINK)

clean	:
	$(MAKE) -C ../lib/sha256 clean
	$(MAKE) -C ../lib/read_file clean
	$(MAKE) -C ../lib/strutils clean
	$(RM) $(OBJS)

fclean	:	clean
	$(MAKE) -C ../lib/sha256 fclean
	$(MAKE) -C ../lib/read_file fclean
	$(MAKE) -C ../lib/strutils fclean
	$(RM) $(NAME)

re	:	fclean	all

.PHONY	:	all clean fclean re	
