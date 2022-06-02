SRCS = srcs/ft_putchar.c srcs/ft_swap.c srcs/ft_putstr.c srcs/ft_strlen.c srcs/ft_strcmp.c
OBJS = $(SRCS:.c=.o)
INCS = includes
CC = gcc
NAME = libft.a
LIBC = ar rc
INCLUDES = -I $(INCS)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o) $(INCLUDES)

$(NAME): $(OBJS)
	$(LIBC) $(NAME) $(OBJS)
	$(LIBC) $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean alll

norm:
	norminette -R CheckForbiddenSourceHeader */*.[ch]

.PHONY all clean fclean re .c.o norm