/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 10:55:11 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/07 11:37:57 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

void	ft_print_decimal(char c)
{
	write(1, &c, 1);
}

void	ft_print_hexadecimal(char c)
{
	unsigned char	hexa;
	char			*base;

	hexa = c;
	base = "0123456789abcdef";
	write(1, "\\", 1);
	write(1, &base[hexa / 16], 1);
	write(1, &base[hexa % 16], 1);
}

void	ft_putstr_non_printable(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] < 32 || str[i] > 126))
			ft_print_decimal(str[i]);
		else
			ft_print_hexadecimal(str[i]);
		i++;
	}
}
