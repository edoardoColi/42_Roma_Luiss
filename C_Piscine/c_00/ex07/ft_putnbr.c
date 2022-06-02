/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 18:19:50 by ecoli             #+#    #+#             */
/*   Updated: 2021/11/28 19:16:20 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_itr(int nb)
{
	char	c;
	char	bar;
	char	zero;
	int		tmp;

	bar = '-';
	zero = '0';
	if (nb < 0)
	{
		write(1, &bar, 1);
		nb = -nb;
	}
	if (nb != 0)
	{
		tmp = nb % 10;
		c = tmp + '0';
		ft_putnbr_itr(nb / 10);
		write(1, &c, 1);
	}
}

void	other25(int nb)
{
	char	c;
	char	zero;
	int		tmp;

	zero = '0';
	if (nb == 0)
		write(1, &zero, 1);
	else
	{
		tmp = nb % 10;
		c = tmp + '0';
		ft_putnbr_itr(nb / 10);
		write(1, &c, 1);
	}
}

void	ft_putnbr(int nb)
{
	char	bar;
	char	zero;
	int		tmp;
	int		check;

	bar = '-';
	zero = '0';
	check = 0;
	if (nb == -2147483648)
	{
		check = 1;
		nb = -214748364;
	}
	if (nb < 0)
	{
		write(1, &bar, 1);
		nb = -nb;
	}
	other25(nb);
	if (check)
	{
		tmp = 8 + '0';
		write(1, &tmp, 1);
	}
}
