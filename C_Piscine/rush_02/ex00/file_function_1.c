/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_function_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 17:27:18 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/12 17:40:00 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"
#include "functions.h"

int	my_atoi(char *str)
{
	int	n;
	int	i;

	i = 0;
	n = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			n = n * 10 + (str[i] - '0');
		}
		else
			return (-1);
		i++;
	}
	return (n);
}

int	is_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (-1);
		i++;
	}
	return (1);
}

char	*nome_key(char *str)
{
	int	i;

	i = 0;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	while (str[i] == ' ' || str[i] == ':' || str[i] == '0')
		i++;
	return (&str[i]);
}

int	is_printable(char c)
{
	if (c < 32 || c > 126)
		return (0);
	else
		return (1);
}

char	*tastiera(char *input)
{
	int		i;
	char	c;

	i = 0;
	while (read(in, &c, SIZE_1B) && c != '\n')
	{
		input[i] = c;
		i++;
	}
	input[i] = '\0';
	return (input);
}
