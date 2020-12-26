CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
AR	= ar
AFLAGS	= -rcs
SRCS	= srcs/atomd5.c
OBJS	= $(SRCS:.c=.o)
INCLUDES	= -Iincludes
NAME	= libatomd5.a
RM	= rm -f

all	:	$(NAME)

.c.o	:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME)	:	$(OBJS)
	$(AR) $(AFLAGS) $(NAME) $(OBJS)

clean	:
	$(RM) $(OBJS)

fclean	: clean
	$(RM) $(NAME)

re	:	fclean all

.PHONY	:	clean fclean all re
