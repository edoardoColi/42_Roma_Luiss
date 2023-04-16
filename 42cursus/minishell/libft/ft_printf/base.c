/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:05:43 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 14:22:46 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//find final char that ends the % stack
int	found_terminator(char ch)
{
	if (ch == 'c' || ch == 's' || ch == 'p' || ch == 'd' || ch == 't'
		|| ch == '%' || ch == 'i' || ch == 'u' || ch == 'x' || ch == 'X'
		|| ch == 'y')
		return (1);
	return (0);
}

// Find % and set str pointer pos to the char next to it
char	*find_percent(char *str)
{
	while (*str)
	{
		if (str[0] == '%' && str[1] != '%')
			return (++str);
		else if (str[0] == '%')
			str++;
		str++;
	}
	return (str);
}

// Print string until the value that we're going to print
void	print_previous_part(char *str, size_t max, t_pflags *tf)
{
	size_t	i;

	i = 0;
	while (i < max)
	{
		if (str[i] == '%' && str[i + 1] == '%')
		{
			pf_putchar_fd('%', 1, tf);
			i++;
		}
		else if (str[i] != '%')
			pf_putchar_fd(str[i], 1, tf);
		i++;
	}
}
