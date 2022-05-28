/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 13:13:47 by eddy              #+#    #+#             */
/*   Updated: 2022/05/28 02:32:50 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
n: Number to check.
Return the absolute value of the number.
*/
long	absolut(long n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

/*
dim: Length of the list.
list: List of numbers.
Return the largest value in the list.
*/
long	get_max(int dim, long list[])
{
	long	max;
	int		i;

	max = list[0];
	i = 0;
	while (i < dim && list[i] != 0)
	{
		if (list[i] > max)
			max = list[i];
		i++;
	}
	return (max);
}

/*
dim: Length of the list.
list: List of numbers.
Return the smallest value in the list.
*/
long	get_min(int dim, long list[])
{
	long	min;
	int		i;

	i = 0;
	min = list[0];
	while (i < dim && list[i] != 0)
	{
		if (list[i] < min)
			min = list[i];
		i++;
	}
	return (min);
}

/*
list: List of numbers.
dim: Length of the list.
direction: Direction for where to shift.
Moves the list by adding a place at the top if direction is positive, remove the first element if direction is negative.
*/
void	scroll(long list[], int dim, int direction)
{
	int		i;
	long	tmp;

	if (direction == +1)			//Scroll to the bottom
	{
		i = dim - 1;
		tmp = list[i];
		while (i > 0)
		{
			if (!(list[i] == 0 && list[i - 1] == 0))
				list[i] = list[i - 1];
			i--;
		}
		list[0] = tmp;
	}
	if (direction == -1)			//Scroll to the top
	{
		i = 0;
		tmp = list[i];
		while (i < dim - 1 && list[i] != 0)
		{
			list[i] = list[i + 1];
			i++;
		}
		list[dim - 1] = tmp;
	}
}

/*
list: List of numbers.
size: Length of the list.
val: Number to check.
idx: Index where the number to be checked is located.
Return true if the value is sorted by the numbers before and after, false otherwise.
*/
int	in_middle(long list[], long size, long val, long idx)
{
	long	tmp;

	if (idx == 0)
		tmp = size;
	else
		tmp = idx;
	if (val < list[idx] && val > list[tmp - 1])
		return (true);
	else if (list[idx] == get_min(size, list)
		&& list[tmp - 1] == get_max(size, list)
		&& ((val < list[idx] && val < list[tmp - 1]) || (val > list[idx] && val > list[tmp - 1])))
		return (true);
	else
		return (false);
}
