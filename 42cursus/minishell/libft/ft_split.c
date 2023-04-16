/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:14:19 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 14:22:46 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	segments_finder(const char *s, char c)
{
	int	i;
	int	segments;

	i = 0;
	segments = 0;
	if (s[0] == c)
		segments -= 1;
	while (s[i])
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			segments += 1;
		i += 1;
	}
	segments += 1;
	return (segments);
}

char	*malloc_segment(const char *s, char c)
{
	char	*segment;
	int		i;
	int		j;

	i = 0;
	while (s[i] && s[i] != c)
		i += 1;
	segment = (char *) malloc(sizeof(char) * (i + 1));
	if (!segment)
		return (NULL);
	j = 0;
	while (j < i)
	{
		segment[j] = s[j];
		j++;
	}
	segment[j] = 0;
	return (segment);
}

char	**ft_split(const char *s, char c)
{
	char	**arr;
	int		segments;
	int		i;

	if (!s)
		return (NULL);
	segments = segments_finder(s, c);
	arr = (char **) malloc(sizeof(char *) * (segments + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s += 1;
		if (*s && *s != c)
		{
			arr[i] = malloc_segment(s, c);
			while (*s && *s != c)
				s += 1;
			i += 1;
		}
	}
	arr[i] = NULL;
	return (arr);
}
