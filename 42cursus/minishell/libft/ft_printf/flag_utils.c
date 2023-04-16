/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:05:12 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 14:22:46 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	reset_struct(t_pflags *tf)
{
	tf->minus = 0;
	tf->plus = 0;
	tf->hash = 0;
	tf->space = 0;
	tf->zero = 0;
	tf->length = 0;
	tf->point = 0;
	tf->prec = 0;
	tf->type = 'V';
}

void	check_flags(t_pflags *tf)
{
	if (tf->space == 1 && tf->plus == 1 && tf->type != 's')
		tf->space = 0;
	if (tf->zero == 1 && tf->minus == 1)
		tf->zero = 0;
	if (tf->zero && tf->point)
		tf->zero = 0;
	if (tf->type == 'c' && tf->zero)
		tf->zero = 0;
}

char	*set_precision(char *str, t_pflags *tf)
{
	int	i;

	i = 1;
	tf->point = 1;
	while (isdigitaft(str[i], 48))
		tf->prec = str[i++] - 48 + tf->prec * 10;
	return ((char *)(str + (i - 1)));
}

char	*set_flags(char *str, t_pflags *tf)
{
	while (*str)
	{
		if (str[0] == '#')
			tf->hash = 1;
		else if (str[0] == '.')
			str = set_precision(str, tf);
		else if (str[0] == ' ')
			tf->space = 1;
		else if (str[0] == '+')
			tf->plus = 1;
		else if (str[0] == '-')
			tf->minus = 1;
		else if (isdigitaft(str[0], 49) || (str[0] == '0' && tf->length > 0))
			tf->length = str[0] - 48 + tf->length * 10;
		else if (str[0] == '0')
			tf->zero = 1;
		else if (found_terminator(str[0]))
		{
			tf->type = str[0];
			return (++str);
		}
		str++;
	}
	return (str);
}
