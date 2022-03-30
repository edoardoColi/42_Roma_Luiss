/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:57:12 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/24 11:54:27 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
s1: The prefix string.
s2: The suffix string.
Return the new string.
NULL if the allocation fails.
Allocates (with malloc(3)) and returns a new
string, which is the result of the concatenation
of ’s1’ and ’s2’.
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;		//Return value
	size_t	l_s1;
	size_t	l_s2;
	
	if (s1 && s2)
	{
		l_s1 = ft_strlen(s1);
		l_s2 = ft_strlen(s2);
		str = malloc(sizeof(char) * (l_s1 + l_s2 + 1));
		if (str)
		{
			ft_memcpy(str, s1, l_s1);
			ft_memcpy(str + l_s1, s2, l_s2);
			str[l_s1 + l_s2] = '\0';
			return (str);
		}
	}
	return (NULL);
}
