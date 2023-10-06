# Program for compiling C programs
CC		= c++
# Extra flags to give to the C preprocessor and programs that use it
CPPFLAGS= -I .
# Extra flags to give to the processor C compiler
CFLAGS	= -std=c++98 -Wall -Werror -Wextra
# Optimization flag to give to the processor C compiler
COPTFLAGS	= -O3

#
SRC		= BitcoinExchange.cpp \
			main.cpp
OBJ		= $(SRC:.cpp=.o)
NAME	= btc
#
.PHONY: all clean fclean re

.o: .cpp
	$(CC) -c $(CFLAGS) $(COPTFLAGS) $(CPPFLAGS) $< -o $@

all: $(NAME)
	@if [ ! -f data.csv ]; then tar xzvf ex00_files.tgz; fi

$(OBJ): BitcoinExchange.hpp

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(COPTFLAGS) -o $@ $(OBJ)

clean:
	rm -f *~ $(OBJ)

fclean: clean
	rm -f $(NAME) input.txt data.csv

re: fclean all
