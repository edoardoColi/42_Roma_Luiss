NAME = get_next_line
BUFFER = 42
CC = gcc
FLAGS = -Wall -Wextra -Werror
BSIZE = -D BUFFER_SIZE=$(BUFFER)
FILES = get_next_line_utils.c \
get_next_line.c
OFILES = $(FILES:.c=.o)

all: $(NAME)

$(NAME): $(OFILES)
	ar rcs $(NAME).a $(OFILES)

$(OFILES):
	$(CC) $(FLAGS) $(BSIZE) -c $(NAME).h $(FILES)

clean:
	rm -f *.o

aclean: 
	rm -f $(NAME).a

fclean: aclean clean

re: fclean
	make