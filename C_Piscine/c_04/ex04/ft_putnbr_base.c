/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:53:51 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/15 14:53:56 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int 	check_acceptable_base(char * base)
{
	int	i;
	int count;

	i = 0;
	count = 0;
	while (base[i] != '\0')
	{
		count++;



		i++;
	}
	if (count < 2)
		return (0);
	return (1);
}

void	ft_putnbr_base(int nbr, char *base)
{
	int	i;

	i = 0;
	if (check_acceptable_base(base))
	{
//TODO
	}
}
