/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:57:25 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/31 13:34:12 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static ssize_t	ft_strlen(const char *s);

/*
s: The string to print.
count: Reference to the printed character counter.
Print the string and increments 
the counter for each character printed.
*/
void	case_string(char *s, ssize_t *count)
{
	ssize_t	l;

	if (!s)
	{
		write(out, "(null)", 6);
		*count = *count + 6;
		return ;
	}
	l = ft_strlen(s);
	write(out, s, l);
	*count = *count + l;
}

/*
s: The string passed.
Return the size of the string.
*/
static ssize_t	ft_strlen(const char *s)
{
	size_t	l;

	l = 0;
	while (s[l] != '\0')
		l++;
	return (l);
}
