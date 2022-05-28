/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_more_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 15:43:46 by eddy              #+#    #+#             */
/*   Updated: 2022/05/28 02:31:39 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
len: Length of the list.
list: List of numbers to check.
Return true if there are no duplicate elements, false otherwise.
*/
int	unicity(int len, long list[])
{
	int	i;
	int	j;

	i = 0;
	while (i < len)
	{
		j = i + 1;
		while (j < len)
		{
			if (list[i] == list[j])
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

/*
dim: Maximum length of the list.
list: List of numbers.
Return the length.
*/
int	arr_len(int dim, long list[])
{
	int	count;

	count = 0;
	while (count < dim && list[count] != 0)
		count++;
	return (count);
}

/*
dim: Length of the list.
num: Item to check.
list: List of numbers.
Return true if the element is present in the list, false otherwise.
*/
int	is_in(int dim, long num, long list[])
{
	int	i;

	i = 1;
	while (i < dim && list[i] != 0)
	{
		if (list[i] == num)
		{
			list[0]--;
			return (true);
		}
		i++;
	}
	return (false);
}

/*
dim: Length of the list.
num: The number to search for.
list: List of numbers.
Return the position of the passed element starting from the top and -1 otherwise.
*/
int	get_idx(int dim, long num, long list[])
{
	int	i;

	i = 0;
	while (i < dim && list[i] != 0)
	{
		if (list[i] == num)
			return (i);
		i++;
	}
	return (-1);
}
