# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft_creator.sh                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ecoli <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/16 15:39:57 by ecoli             #+#    #+#              #
#    Updated: 2021/12/16 15:39:59 by ecoli            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

rm -f libft.a
find . name "*.c" -type f -maxdepth 1 -exec gcc -Wall -Werror -Wextra -c {} \
ar  -rcs libft.a *.o
find / -name "*.o" -type f -maxdepth 1 -delete