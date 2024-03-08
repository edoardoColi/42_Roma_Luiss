# Program for compiling C programs
CC		= c++
# Extra flags to give to the C preprocessor and programs that use it
CPPFLAGS= -I .
# Extra flags to give to the processor C compiler
CFLAGS	= -Wall -Werror -Wextra -std=c++98
# Optimization flag to give to the processor C compiler
COPTFLAGS	= -O3
# Library flags or names given to compilers when they are supposed to invoke the linker, ‘ld’. LOADLIBES is a deprecated (but still supported) alternative to LDLIBS. Non-library linker flags, such as-L, should go in the LDFLAGS variable
LDLIBS	= 

#
SRC		= main.cpp \
			Parser.cpp \
			Server.cpp \
			Location.cpp
OBJ		= $(SRC:.cpp=.o)
NAME	= a.out
#
.PHONY: all clean fclean re

.o: .cpp
	$(CC) -c $(CFLAGS) $(COPTFLAGS) $(CPPFLAGS) $< -o $@

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(COPTFLAGS) -o $@ $(OBJ) $(LDLIBS)

clean:
	rm -f *~ $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
