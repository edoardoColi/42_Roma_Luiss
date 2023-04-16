NAME 		= libft.a
BUFFER 		= 42
BSIZE 		= -D BUFFER_SIZE=$(BUFFER)
CC 			= gcc
FLAGS 		= -Wall -Wextra -Werror
SUBDIRS 	= ft_printf ft_printf/printers get_next_line
DIR_OBJ 	= ./obj
OBJS 		= $(SRCS:.c=.o)
INC_DIRS 	= -I./ $(addprefix -I, $(SUBDIRS))
INCS 		= libft.h ft_printf.h get_next_line.h
HDRS 		= libft.h ft_printf/ft_printf.h get_next_line/get_next_line.h
SRCS 		= ft_atoi.c	ft_lstiter.c ft_strcmp.c ft_bzero.c	ft_lstlast.c \
ft_strdup.c ft_calloc.c	ft_lstmap.c	ft_striteri.c ft_duplicated_x_element.c \
ft_lstnew.c	ft_strjoin.c ft_fill_i_array.c ft_lstsize.c	ft_strlcat.c \
ft_free_cmatrix.c ft_memchr.c ft_strlcpy.c ft_isalnum.c ft_memcmp.c ft_strlen.c \
ft_isalpha.c ft_memcpy.c ft_strmapi.c ft_isascii.c ft_memmove.c ft_strncmp.c \
ft_isdigit.c ft_memset.c ft_strnstr.c ft_isprint.c ft_putchar_fd.c \
ft_strrchr.c ft_issign.c ft_putendl_fd.c ft_strrncmp.c ft_itoa.c \
ft_putnbr_fd.c ft_strtrim.c ft_lstadd_back.c ft_putstr_fd.c ft_substr.c \
ft_lstadd_front.c ft_split.c ft_tolower.c ft_lstclear.c ft_str_is_int.c \
ft_toupper.c ft_lstdelone.c ft_strchr.c ft_printf/base.c \
ft_printf/flag_utils.c ft_printf/ft_printf.c ft_printf/put_things_aside.c \
ft_printf/printers/common_prints.c ft_printf/printers/flag_prints.c \
ft_printf/printers/print_c.c ft_printf/printers/print_di.c \
ft_printf/printers/print_p.c ft_printf/printers/print_s.c \
ft_printf/printers/print_t.c ft_printf/printers/print_u.c \
ft_printf/printers/print_x.c ft_printf/printers/print_y.c \
ft_printf/printers/printers.c get_next_line/get_next_line.c \
get_next_line/get_next_line_utils.c \
ft_pow.c ft_sqrt.c ft_module.c ft_isspace.c ft_isnotspace.c \
ft_isquote.c ft_filliarrayto_n.c ft_isredirection.c ft_free_ptr.c \
ft_arrdup.c ft_print_matrix.c ft_cmtxlen.c \
ft_move_cptr.c ft_arraylen.c

all: $(NAME)

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

%.o: %.c $(HDRS)
	$(CC) $(BSIZE) -o $@ $(FLAGS) -c $< -I.

clean:
	rm -rf $(OBJS)

fclean:
	rm -rf *.o ft_printf/*.o ft_printf/printers/*.o get_next_line/*.o
	rm -rf $(NAME)

bonus: all

re: fclean all
