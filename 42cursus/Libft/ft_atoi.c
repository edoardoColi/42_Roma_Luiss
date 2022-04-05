/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:51:14 by ecoli             #+#    #+#             */
/*   Updated: 2022/04/05 19:11:17 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
My own function implementing the original one.
For more use "man _atoi" 
*/
int	ft_atoi(const char *str)
{
	int					i;
	int					s;
	unsigned int		ret;

	s = 1;
	i = 0;
	ret = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')	//Are the various types of spaces
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		ret = ret * 10 + (str[i] - 48);		//Subtracting the offset of 0, according to the asci table, we get the char as a number
		i++;
	}
	return (s * ret);
}
