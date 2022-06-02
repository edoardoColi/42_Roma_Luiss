CC	= gcc
LIBC	= ar rc
CFLAGS	+= -Wall -Werror -Wextra
OPTFLAGS= -O3
SRC	= .
INCLUDES= -I $(SRC)
LDFLAGS	= -L .
SRC	= main.c file_function5.c file_function4.c file_function3.c file_function2.c file_function1.c
OBJS	= $(SRC:.c=.o)			#Lista dei file in SRC che hanno .c in .o
TARGETS	= BSQ

.PHONY: all clean fclean re norma
.SECONDARY: $(OBJS)

$(TARGETS): $(OBJS)
	$(CC) $(CFLAGS) $(OPTFLAGS) $^ -o $@

.o: .c
	$(CC) $(CFLAGS) $(INCLUDES) $(OPTFLAGS) -c $< -o $@

all: $(TARGETS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f *~ $(TARGETS)

re: fclean all

norma:
	norminette -R CheckForbiddenSourceHeader $(SRC)
