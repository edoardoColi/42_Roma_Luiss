/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:00:59 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/19 14:19:36 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
s: The string from which to create the substring.
start: The start index of the substring in the
string ’s’.
len: The maximum length of the substring.
Return the substring.
NULL if the allocation fails.
Allocates (with malloc(3)) and returns a substring
from the string ’s’.
The substring begins at index ’start’ and is of
maximum size ’len’.
*/
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;		//Return value
	size_t	s_len;
	size_t	i;

	if (s)
	{
		s_len = ft_strlen(s);
		if (start >= s_len)
			return (ft_calloc(1, 1));		//Don't know exactly why
		if (s_len > len)
			substr = malloc(sizeof(char) * (len + 1));
		else
			substr = malloc(sizeof(char) * (s_len + 1));
		if (substr)
		{
			i = 0;
			while (i < len && i + start < s_len)
			{
				substr[i] = s[start + i];
				i++;
			}
			substr[i] = '\0';
			return (substr);
		}
	}
	return (NULL);
}
