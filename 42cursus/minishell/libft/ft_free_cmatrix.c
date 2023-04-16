/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_cmatrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:08:43 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 14:22:46 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_cmatrix(char **mtx)
{
	int	i;

	i = -1;
	if (mtx)
	{
		while (mtx[++i] && mtx[i][0])
			free(mtx[i]);
		free(mtx);
	}
}

void	ft_free_imatrix(int **mtx)
{
	int	i;

	i = 0;
	if (mtx)
	{
		while (mtx[i])
			free(mtx[i++]);
		free(mtx);
	}
}
