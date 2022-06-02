/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_next_prime.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:53:51 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/16 18:30:19 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_is_prime(int nb)
{
	int	i;

	i = 2;
	if (nb < 2)
		return (0);
	if (nb == 2 || nb == 3)
		return (1);
	while (i <= nb / 2)
	{
		if (nb % i == 0)
			return (0);
		i++;
	}
	return (1);
}

int	ft_find_next_prime(int nb)
{
	int	i;

	if (nb <= 0)
		return (1);
	i = nb;
	while (1)
	{
		if (ft_is_prime(i))
			return (i);
		i = i + 2;
	}
}
