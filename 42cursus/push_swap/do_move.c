/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 01:31:15 by eddy              #+#    #+#             */
/*   Updated: 2022/05/28 02:28:15 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
move: The string relating to the move.
listA: The list of numbers in A.
listB: The list of numbers in B.
dim: The size of lists A and B.
Modifies lists A and B following the move that has been chosen.
*/
void	do_move(char *move, long listA[], long listB[], int dim)
{
	long	tmp;

	if (ft_strncmp(move, "sa\0", 3) == 0)			//Makes the move sa
	{
		if (arr_len(dim, listA) > 1)
		{
			tmp = listA[0];
			listA[0] = listA[1];
			listA[1] = tmp;
		}
		write(out, "sa\n", 3);
	}
	else if (ft_strncmp(move, "sb\0", 3) == 0)		//Makes the move sb
	{
		if (arr_len(dim, listB) > 1)
		{
			tmp = listB[0];
			listB[0] = listB[1];
			listB[1] = tmp;
		}
		write(out, "sb\n", 3);
	}
	else if (ft_strncmp(move, "ss\0", 3) == 0)		//Makes the move ss
	{
		if (arr_len(dim, listA) > 1)
		{
			tmp = listA[0];
			listA[0] = listA[1];
			listA[1] = tmp;
		}
		if (arr_len(dim, listB) > 1)
		{
			tmp = listB[0];
			listB[0] = listB[1];
			listB[1] = tmp;
		}
		write(out, "ss\n", 3);
	}
	else if (ft_strncmp(move, "pa\0", 3) == 0)		//Makes the move pa
	{
		if (arr_len(dim, listB) > 0)
		{
			scroll(listA, dim, +1);
			listA[0] = listB[0];
			scroll(listB, dim, -1);
			listB[dim - 1] = 0;
		}
		write(out, "pa\n", 3);
	}
	else if (ft_strncmp(move, "pb\0", 3) == 0)		//Makes the move pb
	{
		if (arr_len(dim, listA) > 0)
		{
			scroll(listB, dim, +1);
			listB[0] = listA[0];
			scroll(listA, dim, -1);
			listA[dim - 1] = 0;
		}
		write(out, "pb\n", 3);
	}
	else if (ft_strncmp(move, "ra\0", 3) == 0)		//Makes the move ra
	{
		tmp = arr_len(dim, listA);
		scroll(listA, dim, -1);
		listA[tmp - 1] = listA[dim - 1];
		if (tmp != dim)
			listA[dim - 1] = 0;
		write(out, "ra\n", 3);
	}
	else if (ft_strncmp(move, "rb\0", 3) == 0)		//Makes the move rb
	{
		tmp = arr_len(dim, listB);
		scroll(listB, dim, -1);
		listB[tmp - 1] = listB[dim - 1];
		if (tmp != dim)
			listB[dim - 1] = 0;
		write(out, "rb\n", 3);
	}
	else if (ft_strncmp(move, "rr\0", 3) == 0)		//Makes the move rr
	{
		tmp = arr_len(dim, listA);
		scroll(listA, dim, -1);
		listA[tmp - 1] = listA[dim - 1];
		if (tmp != dim)
			listA[dim - 1] = 0;
		tmp = arr_len(dim, listB);
		scroll(listB, dim, -1);
		listB[tmp - 1] = listB[dim - 1];
		if (tmp != dim)
			listB[dim - 1] = 0;
		write(out, "rr\n", 3);
	}
	else if (ft_strncmp(move, "rra\0", 4) == 0)		//Makes the move rra
	{
		tmp = arr_len(dim, listA);
		scroll(listA, dim, +1);
		if (tmp != dim)
		{
			listA[0] = listA[tmp];
			listA[tmp] = 0;
		}
		write(out, "rra\n", 4);
	}
	else if (ft_strncmp(move, "rrb\0", 4) == 0)		//Makes the move rrb
	{
		tmp = arr_len(dim, listB);
		scroll(listB, dim, +1);
		if (tmp != dim)
		{
			listB[0] = listB[tmp];
			listB[tmp] = 0;
		}
		write(out, "rrb\n", 4);
	}
	else if (ft_strncmp(move, "rrr\0", 4) == 0)		//Makes the move rrr
	{
		tmp = arr_len(dim, listA);
		scroll(listA, dim, +1);
		if (tmp != dim)
		{
			listA[0] = listA[tmp];
			listA[tmp] = 0;
		}
		tmp = arr_len(dim, listB);
		scroll(listB, dim, +1);
		if (tmp != dim)
		{
			listB[0] = listB[tmp];
			listB[tmp] = 0;
		}
		write(out, "rrr\n", 4);
	}
	else
		free_and_error_exit("Invalid move", listA, listB);
//debug_print_lists(dim, listA, listB);
}
