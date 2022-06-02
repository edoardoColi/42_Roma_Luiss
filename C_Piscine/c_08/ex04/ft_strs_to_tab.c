/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs_to_tab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 12:52:48 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/16 15:31:32 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_duplicate(char *str)
{
	int		i;
	char	*c;

	i = 0;
	c = malloc(sizeof(char) * (ft_strlen(str) + 1))
		if (!c)
		return (0);
	while (str[i] != '\0')
	{
		c[i] = str[i];
	}
	c[i] = '\0';
	return (c);
}

struct s_stock_str	*ft_strs_to_tab(int ac, char **av)
{
	int			i;
	t_stock_str	*tab;

	tab = malloc(sizeof(t_stock_str) * (ac + 1));
	if (!tab)
		return (0);
	i = 0;
	while (i < ac)
	{
		tab[i].size = ft_strlen(av[i]);
		tab[i].str = av[i];
		tab[i].copy = ft_duplicate(av[i]);
		i++;
	}
	tab[i].str = 0;
	return (tab);
}
