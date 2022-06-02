/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_function3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 17:51:06 by ebondi            #+#    #+#             */
/*   Updated: 2021/12/14 18:00:33 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include "functions.h"

int	libera1(int n, int fd, char *line)
{
	close(fd);
	free(line);
	return (n);
}

int	**crea_tab(int len_righe, int num_righe)
{
	int	i;
	int	j;
	int	**tab;

	i = 0;
	tab = malloc(sizeof(*tab) * (num_righe + 1));
	if (!tab)
		return (0);
	while (i < num_righe + 1)
	{
		tab[i] = malloc(sizeof(**tab) * (len_righe + 1));
		if (!tab[i])
			return (0);
		j = 0;
		while (j < len_righe + 1)
		{
			if (i == 0 || j == 0)
				tab[i][j] = 0;
			j++;
		}
		i++;
	}
	return (tab);
}

char	*tastiera(char *input)
{
	int		i;
	char	c;

	i = 0;
	while (read(in, &c, SIZE_1B) && c != '\n')
	{
		input[i] = c;
		i++;
	}
	input[i] = '\0';
	return (input);
}
