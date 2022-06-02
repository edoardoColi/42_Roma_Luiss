/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_comb2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 17:20:25 by ecoli             #+#    #+#             */
/*   Updated: 2021/11/28 17:22:30 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_print_int(int i)
{
	char	n;
	char	m;
	int		tmp1;
	int		tmp2;

	tmp1 = i / 10;
	tmp2 = i % 10;
	n = tmp1 + '0';
	m = tmp2 + '0';
	write(1, &n, 1);
	write(1, &m, 1);
}

void	ft_print_comb2(void)
{
	int	i;
	int	y;

	i = 0;
	while (i < 100)
	{
		y = i +1;
		while (y < 100)
		{
			ft_print_int(i);
			write(1, " ", 1);
			ft_print_int(y);
			if (i != 98)
				write (1, ", ", 2);
			y++;
		}
		i++;
	}
}
