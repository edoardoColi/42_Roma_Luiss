/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:24:10 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:06:27 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	print_element(t_pflags *tf, va_list valist)
{	
	if (tf->type == 'c')
		print_c(va_arg(valist, unsigned int), tf);
	else if (tf->type == 's')
		print_s(va_arg(valist, char *), tf);
	else if (tf->type == 'd' || tf->type == 'i')
		print_i(va_arg(valist, int), tf);
	else if (tf->type == 'x' || tf->type == 'X')
		print_x(va_arg(valist, unsigned int), tf);
	else if (tf->type == 'p')
		print_p(va_arg(valist, void *), tf);
	else if (tf->type == 'u')
		print_u(va_arg(valist, unsigned int), tf);
	else if (tf->type == 't')
		print_t(tf);
	else if (tf->type == 'y')
		print_y(tf);
	else if (tf->type == '%')
		pf_putchar_fd('%', 1, tf);
}
