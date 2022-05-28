/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:28:10 by ecoli             #+#    #+#             */
/*   Updated: 2022/05/28 02:34:15 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
dim: Length of the lists.
listA: List of numbers A.
listB: Support list initially empty.
Starts the sorting process, for list A and B, using the allowed moves.
*/
void	push_swap(int dim, long listA[], long listB[])
{
	long	*priority;
	long	*init_liss;									//Contains the Longest Increasing SubSequence
	int		tmp;
	int		tmp2;

	init_liss = get_best_liss(dim, listA, listB);
	if(dim == init_liss[0])
		final_order(dim, listA, listB, init_liss);
	if (special_case(dim, listA))						//If possible make the solution easy
		free_and_ifneeded_exit(true, listA, listB, init_liss);
	tmp = 0;
	tmp2 = init_liss[0];
	while (tmp < dim && init_liss[0] >= 0)
	{
		if (dim - tmp == init_liss[0])					//I still have to find (init_liss[0]) elements and I have seen (dim - tmp)
			break ;
		if (is_in(tmp2 + 1, listA[0], init_liss))		//If they are in the LISS I rotate them at the bottom
			do_move("ra", listA, listB, dim);
		else											//If they are not in the LISS I move them to listB
		{
			do_move("pb", listA, listB, dim);
			if (listB[0] < 0 && dim > 100 )							//Suppose with a uniform distribution around 0
				do_move("rb", listA, listB, dim);
		}
		tmp++;
	}
	free(init_liss);
	while (arr_len(dim, listB) > 0)						//There are still elements of listB to be placed in listA
	{
		priority = count_moves_to(dim, listB, listA);
		if (priority == NULL)
			free_and_error_exit("Fail calculating priority move", listA, listB);
		tmp2 = better_move(arr_len(dim, listB), priority);
		tmp = tmp2;
		while (tmp != 0 && tmp != arr_len(dim, listB))	//Put the element to add to listA on top of listB
		{
			if (tmp > arr_len(dim, listB) / 2)
			{
				do_move("rrb", listA, listB, dim);
				tmp++;
			}
			else
			{
				do_move("rb", listA, listB, dim);
				tmp--;
			}		
		}
		tmp = absolut(priority[tmp2]);
		while (tmp != 0)								//Setup the position where to put the first element of listB
		{
			if (priority[tmp2] < 0)
				do_move("rra", listA, listB, dim);
			else
				do_move("ra", listA, listB, dim);
			tmp--;
		}
		free(priority);
		do_move("pa", listA, listB, dim);
	}
	final_order(dim, listA, listB, 0);
}

/*
dim: Size of the list.
from: List of numbers.
to: List of numbers.
Return the array of shift values ​​for which any element of from can be placed into 
the correct position if it were on top of 'from'.
*/
long	*count_moves_to(int dim, long from[], long to[])
{
	long	*tmp;
	long	i;
	long	j;
	long	size;

	size = arr_len(dim, to);
	i = 0;
	tmp = malloc(sizeof(long) * dim);
	if (!tmp)
		return (NULL);
	while (i < dim)
	{
		j = 0;
		if (from[i] != 0)
		{
			while (j < dim && !in_middle(to, size, from[i], j) && to[j] != 0)	//Find the position in the middle of the numbers where it should be inserted
				j++;
			if (j > size / 2)													//Convenient to go from the bottom
				tmp[i] = j - size;
			else																//Convenient to go from the top
				tmp[i] = j;
		}
		else
			tmp[i] = 0;
		i++;
	}
	return (tmp);
}

/*
dim: Size of the list.
p: List of numbers.
Return the index that has the lowest cost in the array.
*/
int	better_move(int dim, long p[])
{
	int	min;
	int	index;											//Return value
	int	weight;
	int	i;

	min = p[0];
	index = 0;
	i = 0;
	while (i < dim)
	{
		if (i > dim / 2)								//Convenient to go from the bottom
			weight = dim - i;
		else											//Convenient to go from the top
			weight = i;
		if (min > weight + absolut(p[i]))
		{
			min = weight + absolut(p[i]);
			index = i;
		}
		i++;
	}
	return (index);
}

/*
dim: Size of lists.
listA: List of numbers in A.
listB: List of numbers in B.
Return the array containing the best Longest Increasing SubSequence you can do on A.
*/
long	*get_best_liss(int dim, long listA[], long listB[])
{
	int		tmp;
	long	*init_liss;
	long	*tmp_liss;

	tmp = 0;
		init_liss = liss(dim, listA);
	if (init_liss == NULL)
		free_and_error_exit("Liss fail", listA, listB);
	while (tmp < dim)								//Iterating for the longest LISS
	{
		scroll(listA, dim, +1);
		tmp_liss = liss(dim, listA);
		if (tmp_liss == NULL)
		{
			free(init_liss);						//Free before exit
			free_and_error_exit("Liss fail", listA, listB);
		}
		if (tmp_liss[0] > init_liss[0])
		{
			free(init_liss);						//Free the list that not used
			init_liss = tmp_liss;
		}
		else
			free(tmp_liss);
		tmp++;
	}
	return (init_liss);
}

/*
dim: Size of the lists.
listA: List of numbers in A.
listB: List of numbers in B.
init_liss: List of the initial Longest Increasing SubSequence in order to be freed later.
Moves list A putting the smallest element in first position since the rest is already sorted then free the associated memory.
*/
void	final_order(int dim, long listA[], long listB[], long init_liss[])
{
	int	tmp;

	tmp = get_idx(dim, get_min(dim, listA), listA);
	while (tmp != 0 && tmp != dim)				//Puts the minimum in the first position
	{
		if (tmp > dim / 2)
		{
			do_move("rra", listA, listB, dim);
			tmp++;
		}
		else
		{
			do_move("ra", listA, listB, dim);
			tmp--;
		}		
	}
	free_and_ifneeded_exit(true, listA, listB, init_liss);
}
