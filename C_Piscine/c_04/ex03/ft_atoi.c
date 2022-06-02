/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:53:51 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/15 14:53:56 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isspace(char c, char *spaces)
{
	int	i;

	i = 0;
	while (*spaces != '\0')
	{
		if (*spaces == c)
			return (1);
		spaces++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int	i;
	int	segno;
	int	count;

	i = 0;
	segno = 1;
	count = 0;
	while (ft_isspace(str[i], "\f\n\r\t\v "))
	{
		i++;
	}
	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			segno = -segno;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		count = count * 10;
		count = count + (str[i] - '0');
		i++;
	}
	return (segno * count);
}
