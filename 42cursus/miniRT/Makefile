OS		= $(shell uname)
ifeq ($(OS), Linux)
	MLXDIR	= ./minilibx-linux
else #testa la parte non linux ?funziona?
	MLXDIR	= ./../minilibx_mms_20200219
endif
MLXNAME	= mlx

# Program for compiling C programs
CC		= gcc
# Extra flags to give to the C preprocessor and programs that use it
CPPFLAGS= -I. -I$(MLXDIR)
# Extra flags to give to the processor C compiler
CFLAGS	= -g #-Wall -Werror -Wextra
# Optimization flag to give to the processor C compiler
COPTFLAGS	= -O3
# Extra flags to give to compilers when they are supposed to invoke the linker, ‘ld’, such as-L. Libraries (-lfoo) should be added to the LDLIBS variable instead
LDFLAGS	= -L$(MLXDIR)
# Library flags or names given to compilers when they are supposed to invoke the linker, ‘ld’. LOADLIBES is a deprecated (but still supported) alternative to LDLIBS. Non-library linker flags, such as-L, should go in the LDFLAGS variable
ifeq ($(OS), Linux)
	LDLIBS	= -l$(MLXNAME) -lm -lXext -lX11
else
	LDLIBS	= -l$(MLXNAME) -lm -framework OpenGL -framework AppKit
endif

#
SRC		= main.c \
			draw.c \
			triggers.c \
			checker.c \
			utils.c
OBJ		= $(SRC:.c=.o)
NAME	= miniRT
#
.PHONY: all clean fclean cleanall re

.o: .c
	$(CC) -c $(CFLAGS) $(COPTFLAGS) $(CPPFLAGS) $< -o $@

all: check_lib $(NAME)

check_lib:
	@if [ ! -d $(MLXDIR) ]; then \
		tar -xzf $(MLXDIR).tgz; \
	fi

$(OBJ): global.h functions.h

$(NAME): $(OBJ)
ifeq ($(OS), Linux)
	make -C $(MLXDIR)
else
	@(make -C $(MLXDIR)) && (mv  ./../minilibx_mms_20200219/libmlx.dylib .)
endif
	$(CC) $(CFLAGS) $(COPTFLAGS) $(LDFLAGS) -o $@ $(OBJ) $(LDLIBS)

clean:
	rm -f *~ $(OBJ)
	make clean -C $(MLXDIR)

fclean: clean
	rm -f $(NAME)

cleanall: fclean
	rm -fr $(MLXDIR)

re: fclean all
