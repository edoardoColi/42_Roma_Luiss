/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 14:53:51 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/15 14:53:56 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

void	printa(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	diff;

	diff = *(unsigned char *) s1 - *(unsigned char *) s2;
	while (!diff && *s2)
	{
		++s1;
		++s2;
		diff = *(unsigned char *) s1 - *(unsigned char *) s2;
	}
	if (diff < 0)
	{
		return (-1);
	}
	else if (diff > 0)
	{
		return (1);
	}
	return (diff);
}

int	main(int argc, char *argv[])
{
	int		i;
	char	*tmp;

	i = 1;
	while (i < argc - 1)
	{
		if (ft_strcmp(argv[i], argv[i + 1]) > 0)
		{
			tmp = argv[i];
			argv[i] = argv[i + 1];
			argv[i + 1] = tmp;
			i = 1;
		}
		else
			i++;
	}
	i = 1;
	while (i < argc)
	{
		printa(argv[i]);
		write(1, "\n", 1);
		i++;
	}
}
