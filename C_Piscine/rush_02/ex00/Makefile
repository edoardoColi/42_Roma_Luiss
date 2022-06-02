CC	= gcc -g
LIBC	= ar rc
CFLAGS	+= -Wall -Werror -Wextra
OPTFLAGS= -O3
SRC	= .
INCLUDES= -I $(SRC)
LDFLAGS	= -L .
SRC	= 	main.c file_function_1.c file_function_2.c file_function_3.c file_function_4.c file_function_5.c file_function_6.c file_function_7.c	#Prendi tutti i file della directory con .c
OBJS	= $(SRC:.c=.o)			#Lista dei file in SRC che hanno .c in .o
NAME	= rush-02

.PHONY: all clean fclean re norma
.SECONDARY: $(OBJS)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OPTFLAGS) $^ -o $@

.o: .c
	$(CC) $(CFLAGS) $(INCLUDES) $(OPTFLAGS) -c $< -o $@

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f *~ $(NAME)

re: fclean all

norma:
	norminette -R CheckForbiddenSourceHeader $(SRC)
