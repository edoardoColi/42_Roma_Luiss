/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_p.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:24:40 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:06:27 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	print_address(t_pflags *tf, char *res)
{
	int	c;

	c = 2;
	if (tf->plus)
	{
		c++;
		write(1, "+", 1);
	}
	else if (tf->space)
	{
		c++;
		write(1, " ", 1);
	}
	if (res[2] == ')')
		c -= 2;
	else
		write(1, "0x", 2);
	tf->dimension += c;
}

void	pointer_to_hex(unsigned long int val, char *res)
{
	char	*base;
	int		c;

	c = 2;
	base = "0123456789abcdef";
	if (val == 0)
		res[c++] = '0';
	while (val)
	{
		res[c++] = base[val % 16];
		val /= 16;
	}
	c--;
	res[0] = c;
	res[1] = '\0';
}

void	calc_lengths(int len[4], char *res, t_pflags *tf)
{
	len[0] = (res[0] - 1);
	len[1] = (tf->prec - len[0]);
	len[3] = 2;
	if (tf->plus || tf->space)
		len[3]++;
	if (len[1] > 0)
		len[2] = (tf->length - (tf->prec + len[3]));
	else
		len[2] = (tf->length - (len[0] + len[3]));
}

void	print_p(void *pointer, t_pflags *tf)
{
	char	*res;
	int		len[4];

	res = (char *) malloc (sizeof(char) * 19);
	if (!res)
		return ;
	pointer_to_hex((unsigned long int)(pointer), res);
	calc_lengths(len, res, tf);
	print_spaces_before(len[2], tf);
	print_address(tf, res);
	print_zeroes(len[2] - len[3], tf);
	print_precision(len[1], tf);
	print_hex_ptr(res, tf);
	print_spaces_after(len[2], tf);
	free(res);
}
