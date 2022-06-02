/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_function4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:14:41 by ebondi            #+#    #+#             */
/*   Updated: 2021/12/14 18:14:50 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include "functions.h"

int	is_printable(char c)
{
	if (c < 32 || c > 126)
		return (0);
	else
		return (1);
}

void	free_matrix(int **matrix, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

int	error(int n)
{
	write(err, "map error\n", 10);
	return (n);
}

int	my_atoi(char *str, int *num_righe)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
			sum = sum * 10 + (str[i] - '0');
		else
			return (0);
		i++;
	}
	if (*num_righe == sum)
		return (1);
	return (0);
}

int	my_ebf_cmp(char *ebf)
{
	char	tmp;

	tmp = ebf[0];
	ebf[0] = ebf[1];
	ebf[1] = tmp;
	if (ebf[0] == ebf[1])
		return (0);
	else if (ebf[0] == ebf[2])
		return (0);
	else if (ebf[1] == ebf[2])
		return (0);
	return (1);
}
