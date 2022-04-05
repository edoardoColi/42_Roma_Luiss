/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_void.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:57:38 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/31 13:34:59 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	size_num(unsigned long n);
static void		putnbr_itr(unsigned long n);

/*
p: Pointer to a generic element.
count: Reference to the printed character counter.
Print the number in hexadecimal and increments 
the counter for each character printed.
*/
void	case_void(void * p, ssize_t *count)
{
	unsigned long	p_long;
	int				l;

	if (!p)
	{
		write(out, "0x0", 3);
		*count = *count + 3;
		return ;
	}
	p_long = (unsigned long) p;		//Converted to be printed in hexadecimal
	l = size_num(p_long);
	write(out, "0x", 2);
	putnbr_itr(p_long);
	*count = *count + 2 + l;
}

/*
n: the number to print.
Print the number passed.
*/
static void	putnbr_itr(unsigned long n)
{
	char	tmp;
	char	*hexadecimal;

	hexadecimal = "0123456789abcdef";
	if (n != 0)
	{
		tmp = hexadecimal[(n % 16)];		//Adding the offset of 0, according to the asci table, we get the number as a char
		putnbr_itr(n / 16);
		write(out, &tmp, 1);
	}
}

/*
n: The integer to convert.
Return the integer.
Count and return the size of the number in order to become a char.
*/
static size_t	size_num(unsigned long n)
{
	size_t	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n = n / 16;
		i++;
	}
	return (i);
}
