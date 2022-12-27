CC	= gcc -g
LIBC	= ar -rcs
CFLAGS	+= -Wall -Werror -Wextra
OPTFLAGS= -O3
SRC = .
INCLUDES= -I $(SRC)
LDFLAGS	= -L .
SRC1	=	main_server.c \
			client_server_utils.c
SRC2	=	main_client.c \
			client_server_utils.c
OBJS1	= $(SRC1:.c=.o)
OBJS2	= $(SRC2:.c=.o)
NAME1	= server
NAME2	= client

.PHONY: all clean fclean re

.o: .c
	$(CC) $(CFLAGS) $(INCLUDES) $(OPTFLAGS) -c $< -o $@

all: $(NAME1) $(NAME2)

$(NAME1): $(OBJS1)
	$(CC) $(CFLAGS) $(OPTFLAGS) $^ -o $@

$(NAME2): $(OBJS2)
	$(CC) $(CFLAGS) $(OPTFLAGS) $^ -o $@

clean:
	rm -f $(OBJS1) $(OBJS2)

fclean: clean
	rm -f *~ $(NAME1) $(NAME2)

re: fclean all
