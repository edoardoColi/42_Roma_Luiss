/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:29:24 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/19 14:18:31 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wrd_counter(char const *s, char c);
static char		*getnext_wrd(char const *s, char const **s_base, char c);

/*
s: The string to be split.
c: The delimiter character.
Return the array of new strings resulting from the split.
NULL if the allocation fails.
Allocates (with malloc(3)) and returns an array
of strings obtained by splitting ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer.
*/
char	**ft_split(char const *s, char c)
{
	char	**s_split;		//Return value
	size_t	i;
	size_t	p;

	if (s)
	{
		i = 0;
		p = wrd_counter(s, c);
		s_split = malloc(sizeof(char *) * (p + 1));
		if (s_split)
		{
			while (i < p)
			{
				s_split[i] = getnext_wrd(s, &s, c);
				i++;
			}
			s_split[p] = NULL;
			return (s_split);
		}
	}
	return (NULL);
}

/*
s: The string containing the words.
c: The delimiter character.
Return the integer.
Count and return the number of words divided by the
delimiter character.
*/
static size_t	wrd_counter(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if ((s[i + 1] == c || s[i + 1] == '\0') == 1
			&& (s[i] == c || s[i] == '\0') == 0)
			count++;
		i++;
	}
	return (count);
}

/*
s: The string containing the words.
*s:The string to be updated.
c: The delimiter character.
Return the strings resulting from the split.
NULL if the allocation fails.
Allocates (with malloc(3)) and returns a strings
obtained by splitting the first part of ’s’ using the
character ’c’ as a delimiter. The array must end
with a NULL pointer. *s will be updated, and will
no longer point to the removed part.
*/
static char	*getnext_wrd(char const *s, char const **s_base, char c)
{
	char	*wrd;
	size_t	i;
	size_t	to_canc;
	size_t	len_wrd;

	i = 0;
	to_canc = 0;
	len_wrd = 0;
	while (s[i] == c && s[i] != '\0')
	{
		to_canc++;
		i++;
	}
	while (s[i] != c && s[i] != '\0')
	{
		len_wrd++;
		i++;
	}
	wrd = malloc(sizeof(char) * (len_wrd + 1));
	if (!wrd)
		return (NULL);
	ft_memcpy(wrd, s + to_canc, len_wrd);
	wrd[len_wrd] = '\0';
	*s_base = s + to_canc + len_wrd;		//Scroll the string we have at the beginning by removing the word we return
	return (wrd);
}
