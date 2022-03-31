/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_u_decimal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:57:32 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/31 13:34:22 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	size_num(unsigned int n);
static void		putnbr_itr(unsigned int n);

/*
u: Number to print.
count: Reference to the printed character counter.
Print the number and increase the counter for each character printed.
*/
void	case_u_decimal(unsigned int u, ssize_t *count)
{
	unsigned long	u_long;			//We use long to implicitly manage the INT_MIN value
	int				l;

	if (!u)
		write(out, "0", 1);
	u_long = (unsigned long) u;		//Converted to format as the manual says, unsigned decimal notation
	l = size_num(u_long);
	putnbr_itr(u_long);
	*count = *count + l;
}

/*
n: the number to print.
Print the number passed.
*/
static void	putnbr_itr(unsigned int n)
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
static size_t	size_num(unsigned int n)
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
