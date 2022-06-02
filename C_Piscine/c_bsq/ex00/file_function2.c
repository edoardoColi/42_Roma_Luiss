/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_function2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:20:45 by ebondi            #+#    #+#             */
/*   Updated: 2021/12/14 18:26:09 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include "functions.h"

int	**ridimensiona(int **tab, int max, int x, int y)
{
	int	i;
	int	j;

	i = 0;
	while (i < max)
	{
		j = 0;
		while (j < max)
		{
			tab[x - max + 1 + i][y - max + 1 + j] = 2;
			j++;
		}
		i++;
	}
	return (tab);
}

void	step_back(int	**tab, int r,	int c)
{
	int	i;
	int	j;

	i = 1;
	while (i < r + 1)
	{
		j = 1;
		while (j < c + 1)
		{
			if (tab[i][j] != 0)
				tab[i][j] = 1;
		j++;
		}
	i++;
	}
}

int	**resolv_indian(int **m, int num_righe, int len_righe)
{
	int	i;
	int	j;
	int	lato_sq;
	int	coord_xy[2];

	lato_sq = 0;
	i = 1;
	while (i < (num_righe + 1))
	{
		j = 1;
		while (j < (len_righe + 1))
		{
			if (m[i][j] != 0)
				m[i][j] = (min(m[i - 1][j - 1], m[i - 1][j], m[i][j - 1]) + 1);
			if (lato_sq < m[i][j])
			{
				lato_sq = m[i][j];
				assegna(coord_xy, i, j);
			}
			j++;
		}
	i++;
	}
	step_back(m, num_righe, len_righe);
	return (ridimensiona(m, lato_sq, coord_xy[0], coord_xy[1]));
}

void	assegna(int *arr, int i, int j)
{
	arr[0] = i;
	arr[1] = j;
}
