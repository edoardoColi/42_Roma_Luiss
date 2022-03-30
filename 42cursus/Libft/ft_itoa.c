/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:30:15 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/19 14:17:03 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	size_num(int n);

/*
n: the integer to convert.
Return the string representing the integer.
NULL if the allocation fails.
Allocates (with malloc(3)) and returns a string
representing the integer received as an argument.
Negative numbers must be handled.
*/
char	*ft_itoa(int n)
{
	char	*str;		//Return value
	size_t	len;		//Size of the number as a string
	long	n_long;		//We use long to implicitly manage the INT_MIN value

	n_long = (long) n;
	len = size_num(n_long);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	str[len--] = '\0';
	if (n_long == 0)
		str[0] = '0';
	if (n_long < 0)
	{
		str[0] = '-';
		n_long = n_long * -1;
	}
	while (n_long > 0)
	{
		str[len] = (n_long % 10) + '0';		//Adding the offset of 0, according to the asci table, we get the number as a char
		n_long = n_long / 10;
		len--;
	}
	return (str);
}

/*
n: the integer to convert.
Return the integer.
Count and return the size of the number in order to become a char.
*/
static size_t	size_num(int n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}
