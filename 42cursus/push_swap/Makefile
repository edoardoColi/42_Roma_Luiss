CC	= gcc -g
LIBC	= ar -rcs
CFLAGS	+= -Wall -Werror -Wextra
OPTFLAGS= -O3
SRC = .
INCLUDES= -I $(SRC)
LDFLAGS	= -L .
SRC	=	main.c \
		ft_split_fromLibft.c \
		debug_utils.c \
		push_swap.c \
		liss.c \
		do_move.c \
		special_case.c \
		utils.c \
		more_utils.c \
		more_more_utils.c
OBJS	= $(SRC:.c=.o)
NAME	= push_swap
VG	= valgrind
VGFLAGS	+= --leak-check=yes --track-origins=yes --leak-check=full --show-leak-kinds=all

#If the first argument is "leaks"
ifeq (leaks,$(firstword $(MAKECMDGOALS)))
  #use the rest as arguments for "leaks"
  LEAKS_ARGS := $(wordlist 2,$(words $(MAKECMDGOALS)),$(MAKECMDGOALS))
  #and turn them into do-nothing targets
  $(eval $(LEAKS_ARGS):;@:)
endif

.PHONY: all clean fclean re leaks

.o: .c
	$(CC) $(CFLAGS) $(INCLUDES) $(OPTFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OPTFLAGS) $^ -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f *~ $(NAME)

re: fclean all

leaks:
	$(VG) $(VGFLAGS) ./$(NAME) $(LEAKS_ARGS)
