/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_hex_lowcase.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:57:01 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/31 13:32:37 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	size_num(unsigned long n);
static void		putnbr_itr(unsigned long n);

/*s
xlo: Number to print.
count: Reference to the printed character counter.
Print the number in lowercase hexadecimal and increments 
the counter for each character printed.
*/
void	case_hex_lowcase(unsigned int xlo, ssize_t * count)
{
	unsigned long	xlo_long;
	int				l;

	if(!xlo)
		write(out, "0", 1);
	xlo_long = (unsigned long) xlo;			//Converted to format as the manual says, unsigned hexadecimal notation
	l = size_num(xlo_long);
	putnbr_itr(xlo_long);
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

	hexadecimal = "0123456789abcdef";
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
