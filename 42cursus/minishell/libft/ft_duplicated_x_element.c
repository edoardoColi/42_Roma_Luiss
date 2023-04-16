/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_duplicated_x_element.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:08:13 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 14:22:46 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_duplicated_s_element(char **mat)
{
	int	i;
	int	j;

	i = -1;
	while (mat[++i])
	{
		j = i;
		while (mat[++j])
		{
			if (ft_strcmp(mat[i], mat[j]))
				return (1);
		}
	}
	return (0);
}

int	ft_duplicated_i_element(int	*array)
{
	int	i;
	int	j;

	i = -1;
	while (array[++i])
	{
		j = i;
		while (array[++j])
		{
			if (array[i] == array[j])
				return (1);
		}
	}
	return (0);
}
