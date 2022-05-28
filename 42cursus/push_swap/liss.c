/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   liss.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 22:33:17 by eddy              #+#    #+#             */
/*   Updated: 2022/05/28 02:29:09 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

static long	*values(int dim, long tmp[], long list[], long max);

/*
dim: Size of the list.
list: List of numbers.
Return the list of numbers that are part of the longest Longest Increasing SubSequence.
*/
long	*liss(int dim, long list[])
{
	long	*seq;									//Array on which to calculate the return elements
	long	max;
	int		i;
	int		j;
	
	max = 0;
	seq = malloc(sizeof(long) * dim);				//Freed when the return value is calculated
	if (!seq)
		return (NULL);
	i = 0;
	while (i < dim)
	{
		seq[i] = 1;
		j = 0;
		while (j < i)
		{
			if (list[i] > list[j] && seq[i] < (seq[j] + 1))
			seq[i] = seq[j] + 1;
			j++;
		}
		if (max < seq[i])
			max = seq[i];
		i++;
	}
	return (values(dim, seq, list, max));			//Compute the return array
}

/*
dim: Size of the list.
tmp: Support list for the values ​​with which to calculate the final values.
list: List of numbers of the starting list.
max: Length of the longest Longest Increasing SubSequence.
Return the Longest Increasing SubSequence via the input parameters.
*/
long	*values(int dim, long tmp[], long list[], long max)
{
	long	*ret;									//Return value

	ret = ft_calloc(max + 1, sizeof(long));
	ret[0] = max;									//Store the length to be able to use it later without calculating it
	if (!ret)
	{
		free(tmp);
		return (NULL);
	}
	while (dim > 0 && max > 0)
	{
		if (tmp[dim - 1] == max)
		{
			ret[max] = list[dim - 1];				//Takes the corresponding value from listA
			max--;
		}
		dim--;
	}
	free(tmp);
	return (ret);
}
