/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_case.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:28:10 by ecoli             #+#    #+#             */
/*   Updated: 2022/05/28 02:34:26 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
dim: Size of the list.
listA: List of numbers in A.
Return true if list A is of three elements and easily resolvable, false otherwise.
*/
int	special_case(int dim, long listA[])
{
	if (dim == 3)
	{
		if (listA[0] > listA[2])
			write(out, "sa\nrra\n", 7);
		else if (listA[1] > listA[0])
			write(out, "sa\nra\n", 6);
		else if (listA[2] > listA[0])
			write(out, "sa\n", 3);
		return (true);
	}
	return (false);
}
