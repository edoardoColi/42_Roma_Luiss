/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 19:45:26 by ecoli             #+#    #+#             */
/*   Updated: 2022/05/28 02:28:23 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

static void	case_integer(long i);
static void	putnbr_itr(long n);

/*
dim: Size of lists A and B.
listA: List of elements in A.
listB: List of elements in B.
Prints lists A and B putting the values ​​at the top from left to right.
*/
void	debug_print_lists(int dim, long listA[], long listB[])
{
	int	i;

	i = 0;
	write(out, "\nA->", 4);
	while (i < dim)
	{
		if (listA[i] >= 0)
			case_integer(listA[i] - 1);
		else
			case_integer(listA[i]);
		write(out, " ", 1);
		i++;
	}
	write(out, "\nB->", 4);
	i = 0;
	while (i < dim)
	{
		if (listB[i] >= 0)
			case_integer(listB[i] - 1);
		else
			case_integer(listB[i]);
		write(out, " ", 1);
		i++;
	}
	write(out, "\n", 1);
}

/*
i: The number to print.
count: Reference to the printed character counter.
Print the number and increase the counter for each character printed.
*/
static void	case_integer(long i)
{
	if (!i)
		write(out, "0", 1);
	if (i < 0)
	{
		write(out, "-", 1);
		i = i * -1;
	}
	putnbr_itr(i);
}

/*
n: The number to print.
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
