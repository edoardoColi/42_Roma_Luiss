/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_hex_upcase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:57:07 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/31 13:33:40 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	size_num(unsigned long n);
static void		putnbr_itr(unsigned long n);

/*
xup: Number to print.
count: Reference to the printed character counter.
Print the number in uppercase hexadecimal and increments 
the counter for each character printed.
*/
void	case_hex_upcase(unsigned int xup, ssize_t *count)
{
	unsigned long	xup_long;
	int				l;

	if (!xup)
		write(out, "0", 1);
	xup_long = (unsigned long) xup;		//Converted to format as the manual says, unsigned hexadecimal notation
	l = size_num(xup_long);
	putnbr_itr(xup_long);
	*count = *count + l;
}

/*
n: the number to print.
Print the number passed.
*/
static void	putnbr_itr(unsigned long n)
{
	char	tmp;
	char	*hexadecimal;

	hexadecimal = "0123456789ABCDEF";
	if (n != 0)
	{
		tmp = hexadecimal[(n % 16)];		//We take the offset and use it in the reference string
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
