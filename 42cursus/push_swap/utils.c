/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 18:41:12 by ecoli             #+#    #+#             */
/*   Updated: 2022/05/28 02:35:09 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
s: The string containing the words.
c: The delimiter character.
Return the integer.
Count and return the number of words divided by the
delimiter character.
*/
int	counter(char const *s, char c)
{
	int	i;
	int	count;

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
freeifexit: Matrix to be free.
index: Index of the string to convert.
listA: List of numbers.
listB: List of numbers.
Return the number converted from string to integer.
*/
long	to_int(char **freeifexit, int index, long listA[], long listB[])
{
	int		i;
	int		s;
	long	ret;
	char	*str;

	s = 1;
	i = 0;
	ret = 0;
	str = freeifexit[index];
	if (str[i] == '-' || str[i] == '+')			//Convert both numbers written as "-1" and as "+1"
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			ret = ret * 10 + (str[i] - 48);		//Subtracting the offset of 0, according to the asci table, we get the char as a number
		else
		{
			while (freeifexit[index])
			{
				freeifexit[index]=NULL;
				free(freeifexit[index]);
				index++;
			}
			freeifexit = NULL;
			free(freeifexit);
			free_and_error_exit("Some arguments are not integers", listA, listB);
		}
		i++;
	}
	if ((ret + 1 > 2147483648 && s == 1) || (ret > 2147483648 && s == -1))
	{
		while (freeifexit[index])
		{
			free(freeifexit[index]);
			index++;
		}
		free(freeifexit);
		free_and_error_exit("Some integers are out of INT_MIN e INT_MAX bounds", listA, listB);
	}
	if (s * ret >= 0)
		return ((s * ret) + 1);
	return (s * ret);
}

/*
My own function implementing the original one.
For more use "man strncmp" 
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0' && (i < n - 1))
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
My own function implementing the original one.
For more use "man calloc" 
*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*a;
	size_t	space;

	space = count * size;
	a = malloc(space);
	if (!a)
		return (NULL);
	ft_memset(a, 0, space);
	return (a);
}

/*
My own function implementing the original one.
For more use "man memset" 
*/
void	*ft_memset(void *b, int c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		((unsigned char *)b)[i] = c;
		i++;
	}
	return (b);
}
