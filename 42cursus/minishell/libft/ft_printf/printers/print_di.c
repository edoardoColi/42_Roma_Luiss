/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_di.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:24:47 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:06:27 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	print_i(int i, t_pflags *tf)
{	
	if (tf->plus == 1 && i > -1)
		pf_putchar_fd('+', 1, tf);
	else if (i < 0)
		pf_putchar_fd('-', 1, tf);
	if (tf->space == 1 && i > -1)
	{
		pf_putchar_fd(' ', 1, tf);
		print_0s(i, tf, ' ');
	}
	if (tf->zero || tf->point)
		print_0s(i, tf, '0');
	pf_putnbr_fd(i, 1, tf);
	if (tf->minus == 1)
		print_0s(i, tf, ' ');
}
