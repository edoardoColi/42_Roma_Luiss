/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_x.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:24:19 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:06:27 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	print_hex_ptr(char *res, t_pflags *tf)
{
	int	i;

	i = res[0];
	while (i > 1)
		pf_putchar_fd(res[i--], 1, tf);
}

char	*number_to_hex(long int val, t_pflags *tf, char *res)
{
	char	*base;
	int		c;

	if (tf->point && tf->prec == 0 && val == 0)
		return (res);
	c = 2;
	if (val == 0)
		res[c++] = '0';
	if (tf->type == 'x' || tf->type == 'p')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	while (val)
	{
		res[c++] = base [val % 16];
		val /= 16;
	}
	c--;
	res[0] = c;
	res[1] = '\0';
	return (res);
}

void	print_hash(long int val, t_pflags *tf)
{
	if (!val || !tf->hash)
		return ;
	pf_putchar_fd('0', 1, tf);
	if (tf->type == 'x')
		pf_putchar_fd('x', 1, tf);
	else
		pf_putchar_fd('X', 1, tf);
}

void	print_x(long int val, t_pflags *tf)
{
	char	*res;
	int		len[3];

	res = (char *) malloc (sizeof(char) * 19);
	if (!res)
		return ;
	number_to_hex(val, tf, res);
	len[0] = (res[0] - 1);
	len[1] = (tf->prec - len[0]);
	if (len[1] > 0)
		len[2] = (tf->length - tf->prec);
	else
		len[2] = (tf->length - len[0]);
	if (val && tf->hash)
		len[2] += 2;
	print_spaces_before(len[2], tf);
	print_zeroes(len[2], tf);
	print_hash(val, tf);
	print_precision(len[1], tf);
	print_hex_ptr(res, tf);
	print_spaces_after(len[2], tf);
	free(res);
}
