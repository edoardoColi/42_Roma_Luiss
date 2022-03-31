/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_decimal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:56:51 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/31 13:31:08 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	size_num(long n);
static void		putnbr_itr(long n);

/*
d: The number to print.
count: Reference to the printed character counter.
Print the number and increase the counter for each character printed.
*/
void	case_decimal(int d, ssize_t *count)
{
	long	d_long;			//We use long to implicitly manage the INT_MIN value
	int		l;

	if (!d)
		write(out, "0", 1);
	d_long = (long) d;
	l = size_num(d_long);
	if (d_long < 0)
	{
		write(out, "-", 1);
		d_long = d_long * -1;
	}
	putnbr_itr(d_long);
	*count = *count + l;
}

/*
n: the number to print.
Print the number passed.
*/
static void	putnbr_itr(long n)
{
	char	tmp;

	if (n != 0)
	{
		tmp = (n % 10) + '0';		//Adding the offset of 0, according to the asci table, we get the number as a char
		putnbr_itr(n / 10);
		write(out, &tmp, 1);
	}
}

/*
n: The integer to convert.
Return the integer.
Count and return the size of the number in order to become a char.
*/
static size_t	size_num(long n)
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
