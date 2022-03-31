/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:57:44 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/31 13:35:40 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
My own function mimic the original one.
Not everything is handled as in the original.
*/
int	ft_printf(const char *str, ...)
{
	va_list	ap;
	ssize_t	count;
	char	c;

	if (!str)
		return (0);
	count = 0;
	va_start(ap, str);
	while (*str && count >= 0)
	{
		if (*str != '%')
		{
			write(out, &str[0], 1);
			count++;
		}
		else
		{
			c = *++str;
			if (c)
				switch_case(c, ap, &count);
			else
				return (-1);
		}
		c = *++str;
	}
	va_end(ap);
	return (count);
}

/*
c: The character to check.
ap: The list of args.
count: Reference to the printed character counter.
Do switch-case for actually printing passed arguments and 
increment the counter.
*/
void	switch_case(char c, va_list ap, ssize_t *count)
{
	if (c == 'c')
		case_char(va_arg(ap, int), count);
	else if (c == 's')
		case_string(va_arg(ap, char *), count);
	else if (c == 'p')
		case_void(va_arg(ap, void *), count);
	else if (c == 'd')
		case_decimal(va_arg(ap, int), count);
	else if (c == 'i')
		case_integer(va_arg(ap, int), count);
	else if (c == 'u')
		case_u_decimal(va_arg(ap, unsigned int), count);
	else if (c == 'x')
		case_hex_lowcase(va_arg(ap, unsigned int), count);
	else if (c == 'X')
		case_hex_upcase(va_arg(ap, unsigned int), count);
	else if (c == '%')
		case_perc(c, count);
	else				//Default for unmanaged flags
	{
		write(out, "%", 1);
		write(out, &c, 1);
		*count = *count + 2;
	}
}
