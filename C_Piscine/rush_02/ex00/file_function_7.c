/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_function_7.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 18:44:00 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/12 18:48:37 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"
#include "functions.h"

void	libera_tab(char **tab, int num_righe)
{
	int	i;

	i = 0;
	while (i < num_righe)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	libera_diz(t_nodo *succ)
{
	if (succ != 0)
	{
		libera_diz(succ->next);
		free(succ);
	}
}

int	my_atoi2_2(int n)
{
	if (n > 99)
		n = 1;
	return (n);
}
