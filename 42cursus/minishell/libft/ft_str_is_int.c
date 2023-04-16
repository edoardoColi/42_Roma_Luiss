/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:14:30 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 14:22:46 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_is_int(const char *str)
{
	long	num;

	num = ft_atol(str);
	if (num > MAXINT || num < MININT)
		return (0);
	if (ft_issign(str[0]))
		str++;
	while (str++[0])
	{
		if (!ft_isdigit(str[-1]))
			return (0);
	}
	return (1);
}
