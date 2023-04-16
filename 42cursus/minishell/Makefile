CC	=	gcc
CFLAGS	=	-g -Wall -Werror -Wextra
LDLIBS	=	-lreadline
INCS	=	global.h \
				executor.h \
				parser.h \
				lexer.h \
				glob.h \
				redirection.h
SRCS	=	signals2_0.c \
				main.c \
				free_structs.c \
				init.c \
				prompt.c \
				lexer.c \
				lexer_splitter.c \
				lexer_syntax.c \
				parser.c \
				ps_utils.c \
				ps_write.c \
				ps_utils_2.c \
				ps_flags_red.c \
				executor.c \
				ft_execv.c \
				pipe.c \
				redirpipe.c \
				redir.c \
				executor_process.c \
				expander.c \
				expander_utils.c \
				redirector.c \
				unset.c \
				cd.c \
				echo.c \
				env.c \
				pwd.c \
				exit.c \
				export.c \
				export2.c \
				export3.c \
				export_utils2.c \
				red_exec.c \
				redirection.c
LIBFT	=	./libft/libft.a
OBJS	=	$(SRCS:.c=.o)
NAME	=	minishell
#
.PHONY: all clean fclean re

.o: .c
	$(CC) -c $(CFLAGS) $< -o $@

all:$(NAME)

$(LIBFT):
		make -C libft/

$(OBJS): $(INCS)

$(NAME): $(OBJS) $(LIBFT)
		$(CC) $(CFLAGS) $(SRCS) $(LIBFT) $(LDLIBS) -o $(NAME)

clean:
	make clean -C libft/
	rm -f *~ $(OBJS)

fclean:
	make fclean -C libft/
	rm -f *~ $(OBJS)
	rm -f $(NAME)

re: fclean all
