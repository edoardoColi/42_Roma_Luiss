/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:10:04 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 14:22:46 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	calc_digits(int n)
{
	int	digits;

	digits = 1;
	while ((n / 10) > 0)
	{
		n = n / 10;
		digits++;
	}
	return (digits);
}

int	calc_sign(int *n)
{
	int	sign;

	sign = 0;
	if (*n < 0)
	{
		sign = 1;
		*n *= -1;
	}
	return (sign);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		digits;
	int		sign;
	int		i;

	str = 0;
	if (n == -2147483648)
		return (ft_strdup("-2147483648\0"));
	sign = calc_sign(&n);
	digits = calc_digits(n) + sign;
	str = (char *) malloc(sizeof(char) * (digits + 1));
	if (!str)
		return (NULL);
	if (sign == 1)
		str[0] = '-';
	i = digits - 1;
	while (i >= sign)
	{
		str[i] = (char)(n % 10) + '0';
		n /= 10;
		i--;
	}
	str[digits] = '\0';
	return (str);
}
