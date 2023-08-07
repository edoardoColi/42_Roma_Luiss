# Program for compiling C programs
CC		= c++
# Extra flags to give to the C preprocessor and programs that use it
CPPFLAGS= -I .
# Extra flags to give to the processor C compiler
CFLAGS	= -std=c++98 -Wall -Werror -Wextra
# Optimization flag to give to the processor C compiler
COPTFLAGS	= -O3

#
SRC		= AAnimal.cpp \
			WrongAnimal.cpp \
			Cat.cpp \
			WrongCat.cpp \
			Dog.cpp \
			Brain.cpp \
			main.cpp
OBJ		= $(SRC:.cpp=.o)
NAME	= zoo
#
.PHONY: all clean fclean re

.o: .cpp
	$(CC) -c $(CFLAGS) $(COPTFLAGS) $(CPPFLAGS) $< -o $@

all: $(NAME)

$(OBJ): AAnimal.hpp WrongAnimal.hpp Cat.hpp WrongCat.hpp Dog.hpp Brain.hpp

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(COPTFLAGS) -o $@ $(OBJ)

clean:
	rm -f *~ $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
