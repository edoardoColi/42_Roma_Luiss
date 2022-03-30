#Compila tutti i .c che si trovano nella dir
CC	= gcc
LIBC	= ar rc
CFLAGS	+= -Wall -Werror -Wextra
OPTFLAGS= -O3
SRC		= .
INCLUDES= -I$(SRCS)			#ricontrolla se va bene
LDFLAGS	= -L.					#non ricordo a cosa serve
SRCS	= $(wildcard *.c)		#Prendi tutti i file della directory con .c
OBJS	= $(SRCS:.c=.o)			#Lista dei file in SRCS che hanno .c in .o
TARGETS	= bsq				#Nome dell'eseguibile alla fine dal make

.PHONY: all clean fclean re run norma
.SECONDARY: $(OBJS)			#In modo che i .o di compilazione non vengano auto rimossi

%: $(OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(OPTFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) $(OPTFLAGS) -c $^ -o $@

all: $(TARGETS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(OBJS) *~ $(TARGETS)

re: fclean all

norma:					#Creato per provare i flag per 42Roma
	norminette -R CheckForbiddenSourceHeader $(SRC)
