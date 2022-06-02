/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:26:59 by ebondi            #+#    #+#             */
/*   Updated: 2022/06/02 19:04:53 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include "functions.h"

int	main(int argc, char *argv[])
{
	int		i;
	char	ebf[3];
	int		righe[2];
	int		**tab;

	i = 1;
	if (argc == 1)
	{
		prendi_input();				//If I don't have an input configuration I take it from the keyboard
		return (0);
	}
	while (i < argc)
	{
		tab = gen_file_tab(argv[i], ebf, &righe[0], &righe[1]);
		if (tab)
		{
			tab = resolv_indian(tab, righe[0], righe[1]);
			print_matrix(tab, ebf, righe[0], righe[1]);
			free_matrix(tab, righe[0] + 1);
		}
		else
			error(1);
		i++;
	}
	return (0);
}

void	prendi_input(void)
{
	//TODO
}

int	min(int a, int b, int c)
{
	int	min;

	min = a;
	if (b < min)
		min = b;
	if (c < min)
		min = c;
	return (min);
}

int	**chiudi(int **tab, int fd)
{
	close(fd);
	return (tab);
}
