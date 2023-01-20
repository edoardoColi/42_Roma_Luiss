OS	= $(shell uname)
MLXDIR	= ./minilibx-linux/
MLXNAME	= mlx
MLX	= $(MLXDIR)lib$(MLXNAME).a
# Program for compiling C programs
CC	= gcc
# Extra flags to give to the C preprocessor and programs that use it
CPPFLAGS= -I. -I$(MLXDIR)
# Extra flags to give to the processor C compiler
#-Wall -Werror -Wextra
CFLAGS	= -g -Wall -Werror -Wextra
# Optimization flag to give to the processor C compiler
COPTFLAGS	= -O3
# Extra flags to give to compilers when they are supposed to invoke the linker, ‘ld’, such as-L. Libraries (-lfoo) should be added to the LDLIBS variable instead
LDFLAGS	= -L$(MLXDIR)
# Library flags or names given to compilers when they are supposed to invoke the linker, ‘ld’. LOADLIBES is a deprecated (but still supported) alternative to LDLIBS. Non-library linker flags, such as-L, should go in the LDFLAGS variable
LDLIBS	= -lm -lXext -lX11 -lz -l$(MLXNAME)
#
SRC	= main.c
OBJ	= $(SRC:.c=.o)
NAME	= fractol
#
.PHONY: all clean fclean re reall

.o: .c
	$(CC) -c $(CFLAGS) $(COPTFLAGS) $(CPPFLAGS) $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	make -C $(MLXDIR)
	$(CC) $(CFLAGS) $(COPTFLAGS) $(LDFLAGS) -o $@ $^ $(MLX) $(LDLIBS)

clean:
	make clean -C $(MLXDIR)
	rm -f *~ $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

reall: fclean all
	make re -C $(MLXDIR)
