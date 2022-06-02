/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_function1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:17:28 by ebondi            #+#    #+#             */
/*   Updated: 2021/12/14 16:28:08 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include "functions.h"

int	**gen_file_tab(char *file, char *ebf, int *num_righe, int *len_righe)
{
	int	**tab;

	*num_righe = first_look(file, len_righe, ebf);
	if (*num_righe <= 0)
		return (0);
	tab = riempi_tab(file, ebf, *num_righe, *len_righe);
	if (!tab)
		return (0);
	return (tab);
}

int	parse_first_line(char *str, char *ebf, int *num_righe)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
		i++;
	if (i < 4)
		return (0);
	while (j < 3)
	{
		ebf[j] = str[i + j - 3];
		str[i + j - 3] = '\0';
		j++;
	}
	if (!my_ebf_cmp(ebf) || !my_atoi(str, num_righe))
		return (0);
	return (1);
}

void	print_matrix(int **matrix, char *ebf, int num_righe, int len_righe)
{
	int	i;
	int	j;
	int	tmp;

	i = 1;
	while (i < (num_righe + 1))
	{
		j = 1;
		while (j < (len_righe + 1))
		{
			tmp = matrix[i][j];
			write (out, &ebf[tmp], SIZE_1B);
			j++;
		}
		write (out, "\n", SIZE_1B);
		i++;
	}
}

int	trasforma(char c, char *ebf)
{
	if (c == ebf[1])
		return (1);
	else if (c == ebf[0])
		return (0);
	else
		return (-1);
}
