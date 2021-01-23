CC	= gcc
CFLAGS	= -Wall -Werror -Wextra
AR	= ar
AFLAGS	= -rcs
SRCS	= srcs/hash.c
OBJS	= $(SRCS:.c=.o)
INCLUDES	= -Iincludes -I../includes -I$(VLA)/includes
VLA	= ../vla
LINK	= -L $(VLA) -lvla
NAME	= libhash.a
RM	= rm -f

all	:	$(NAME)

.c.o	:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME)	:	$(OBJS)
	$(MAKE) -C $(VLA) all
	$(AR) $(AFLAGS) $(NAME) $(OBJS)

clean	:
	$(MAKE) -C $(VLA) clean
	$(RM) $(OBJS)

fclean	:	clean
	$(MAKE) -C $(VLA) fclean
	$(RM) $(NAME)

re	:	fclean all

.PHONY	:	clean fclean all re
