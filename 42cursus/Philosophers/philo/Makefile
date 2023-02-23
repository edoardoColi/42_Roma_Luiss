CC	= gcc -g
LIBC	= ar -rcs
CFLAGS	+= -pthread -Wall -Werror -Wextra
OPTFLAGS= -O3
SRC = .
INCLUDES= -I $(SRC)
LDFLAGS	= -L .
SRC		=	main.c \
			philo.c \
			demon.c \
			utils.c
OBJS	= $(SRC:.c=.o)
NAME	= philo

.PHONY: all clean fclean re

.o: .c
	$(CC) $(CFLAGS) $(INCLUDES) $(OPTFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) global.h functions.h
	$(CC) $(CFLAGS) $(OPTFLAGS) $(OBJS) -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f *~ $(NAME)

re: fclean all
