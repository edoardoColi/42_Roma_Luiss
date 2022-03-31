CC	= gcc -g
LIBC	= ar -rcs
CFLAGS	+= -Wall -Werror -Wextra
OPTFLAGS= -O3
SRC = .
INCLUDES= -I $(SRC)
LDFLAGS	= -L .
SRC	=	case_char.c\
		case_string.c\
		case_void.c\
		case_decimal.c\
		case_integer.c\
		case_u_decimal.c\
		case_hex_lowcase.c\
		case_hex_upcase.c\
		case_perc.c\
		ft_printf.c
OBJS	= $(SRC:.c=.o)
NAME	= libftprintf.a

.PHONY: all clean fclean re

.o: .c
	$(CC) $(CFLAGS) $(INCLUDES) $(OPTFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(LIBC) $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f *~ $(NAME)

re: fclean all
