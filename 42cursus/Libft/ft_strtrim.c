/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 13:06:34 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/24 11:56:27 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char const *str, char c);

/*
s1: The string to be trimmed.
set: The reference set of characters to trim.
Return the trimmed string.
NULL if the allocation fails.
Allocates (with malloc(3)) and returns a copy of
’s1’ with the characters specified in ’set’ removed
from the beginning and the end of the string.
*/
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*t_str;		//Return value
	size_t	from;		//Start of the cut word
	size_t	to;			//End of the cut word

	if (s1 && set)
	{
		from = 0;
		to = ft_strlen(s1);
		while (is_in(set, s1[from]))
			from++;
		while (is_in(set, s1[to - 1]) && from < to)
			to--;
		t_str = malloc(sizeof(char) * (to - from + 1));
		if (t_str)
		{
			ft_memcpy(t_str, s1 + from, to - from);
			t_str[to - from] = '\0';
			return (t_str);
		}
	}
	return (NULL);
}

/*
str: The reference set of characters to trim.
c: Character to test.
Return boolean value.
If the character is part of the string it
returns true, else false.
*/
static int	is_in(char const *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
