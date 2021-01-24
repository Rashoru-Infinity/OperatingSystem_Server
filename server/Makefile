CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
SRCS	= srcs/main.c srcs/admit.c srcs/gen_repository.c
OBJS	= $(SRCS:.c=.o)
INCLUDES	= -Iincludes -I$(SHA256)/includes -I$(READFILE)/includes -I$(STRUTILS)/includes -I$(VLA)/includes -I$(HASHSET)/includes -I$(LIBTYPES)/includes
SHA256	= ../lib/sha256
READFILE	= ../lib/read_file
STRUTILS	= ../lib/strutils
VLA			= ../lib/vla
HASHSET		= ../lib/hash_set
LIBTYPES	= ../lib
LINK	= -L $(READFILE) -lreadfile -L $(SHA256) -latoSHA256 -L $(STRUTILS) -lstrutils -L $(HASHSET) -lhashset -lcrypto
NAME	= git_server
RM	= rm -f

all	:	$(NAME)

.c.o	:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME)	:	$(OBJS)
	$(MAKE) -C $(SHA256) all
	$(MAKE) -C $(READFILE) all
	$(MAKE) -C $(STRUTILS) all
	$(MAKE) -C $(HASHSET) all
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJS) $(LINK)

clean	:
	$(MAKE) -C $(SHA256) clean
	$(MAKE) -C $(READFILE) clean
	$(MAKE) -C $(STRUTILS) clean
	$(MAKE) -C $(HASHSET) clean
	$(RM) $(OBJS)

fclean	:	clean
	$(MAKE) -C $(SHA256) fclean
	$(MAKE) -C $(READFILE) fclean
	$(MAKE) -C $(STRUTILS) fclean
	$(MAKE) -C $(HASHSET) fclean
	$(RM) $(NAME)

re	:	fclean	all

.PHONY	:	all clean fclean re	
