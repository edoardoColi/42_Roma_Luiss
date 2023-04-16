NAME = libftprintf
CC = gcc
CFLAGS = -Werror -Wextra -Wall
SUBDIRS = printers
DIR_OBJ = ./obj
INCS = $(wildcard *.h $(foreach fd, $(SUBDIRS), $(fd)/*.h))
SRCS = $(wildcard *.c $(foreach fd, $(SUBDIRS), $(fd)/*.c))
OBJS = $(addprefix $(DIR_OBJ)/, $(SRCS:c=o))
INC_DIRS = -I./ $(addprefix -I, $(SUBDIRS))

PHONY := $(NAME)
$(NAME): $(OBJS)
	ar rcs $(NAME).a $(OBJS)

$(DIR_OBJ)/%.o: %.c $(INCS)
	mkdir -p $(@D)
	$(CC) -o $@ $(CFLAGS) -c $< $(INC_DIRS)

PHONY += clean

.PHONY = $(PHONY)

all: $(NAME)

clean:
	rm -r -f obj

aclean: 
	rm -f $(NAME).a

fclean: aclean clean

bonus: all

re: fclean all
