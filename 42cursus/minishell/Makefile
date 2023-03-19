# Program for compiling C programs
CC		= gcc
# Extra flags to give to the C preprocessor and programs that use it
CPPFLAGS= -I .
# Extra flags to give to the processor C compiler
CFLAGS	= -g 
#-Wall -Werror -Wextra
# Optimization flag to give to the processor C compiler
COPTFLAGS	= -O3
# Library flags or names given to compilers when they are supposed to invoke the linker, ‘ld’. LOADLIBES is a deprecated (but still supported) alternative to LDLIBS. Non-library linker flags, such as-L, should go in the LDFLAGS variable
LDLIBS	= -lreadline

#
SRC		= main.c \
			utils.c \
			analyzer.c \
			parser.c \
			builtins.c \
			redirections.c
OBJ		= $(SRC:.c=.o)
NAME	= minishell
#
.PHONY: all clean fclean cleanall re

.o: .c
	$(CC) -c $(CFLAGS) $(COPTFLAGS) $(CPPFLAGS) $< -o $@

all: $(NAME)

$(NAME): $(OBJ) global.h functions.h
	$(CC) $(CFLAGS) $(COPTFLAGS) -o $@ $(OBJ) $(LDLIBS)

clean:
	rm -f *~ $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
