/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 11:46:27 by tde-nico          #+#    #+#             */
/*   Updated: 2022/06/02 18:38:43 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

int	col_is_valid(int **tab, int *clues, int x, int size);
int	line_is_valid(int **tab, int *clues, int y, int size);
int	can_put_value(int **tab, int *pos, int value, int size);
int	search_empty_case(int **tab, int *x, int *y, int size);
int	ft_strlen(char *str);

int	**generate_tab(int size)
{
	int	**tab;
	int	x;
	int	y;

	y = -1;
	tab = malloc(sizeof(*tab) * size);
	while (++y < size)
	{
		x = -1;
		tab[y] = malloc(sizeof(**tab) * size);
		while (++x < size)
			tab[y][x] = 0;
	}
	return (tab);
}

void	display_tab(int **tab, int size)
{
	int		y;
	int		x;
	char	c;

	y = -1;
	while (++y < size)
	{
		x = -1;
		while (++x < size)
		{
			c = tab[y][x];
			write(1, &c, 1);
			if (x != (size - 1))
				write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
}

int	resolve(int **tab, int *clues, int size)
{
	int	x;
	int	y;
	int	value;
	int	pos[2];

	if (search_empty_case(tab, &x, &y, size))
	{
		value = '0';
		while (++value <= (size + '0'))
		{
			pos[0] = x;
			pos[1] = y;
			if (can_put_value(tab, pos, value, size))
			{
				tab[y][x] = value;
				if (x == (size - 1) && !line_is_valid(tab, clues, y, size))
					continue ;
				if (y == (size - 1) && !col_is_valid(tab, clues, x, size))
					continue ;
				if (resolve(tab, clues, size))
					return (1);
			}
		}
		tab[y][x] = 0;
		return (0);
	}
	return (1);
}

int	*arg_check(char *argv, int *size)
{
	int	i;
	int	clue;
	int	len;
	int	*clues;

	i = -1;
	clue = 0;
	len = (ft_strlen(argv) + 1) / 2 ;
	while (*size * 4 < len)
		*size += 1;
	clues = malloc(sizeof(*clues) * *size * 4);
	if (*size * 4 != len || clues == NULL)
		return (NULL);
	while (argv[++i] != '\0')
	{
		if (i % 2 != 0 && argv[i] == ' ')
			continue ;
		if ((i % 2 != 0 && argv[i] != ' '))
			return (NULL);
		if (i % 2 == 0 && !(argv[i] >= '1' && argv[i] <= (*size + '0')))
			return (NULL);
		clues[clue] = argv[i] - '0';
		clue++;
	}
	if (i != (len * 2 - 1))
		return (NULL);
	return (clues);
}

int	main(int argc, char **argv)
{
	int	**tab;
	int	size;
	int	*clues;

	size = 0;
	clues = NULL;
	if (argc == 2)
		clues = arg_check(argv[1], &size);
	if (clues == NULL)
	{
		write(1, "Error\n", 6);
		free(clues);
		return (1);
	}
	tab = generate_tab(size);
	if (!resolve(tab, clues, size))
	{
		write(1, "Error\n", 6);
		free(clues);
		free(tab);
		return (1);
	}
	display_tab(tab, size);
	free(clues);
	free(tab);
	return (0);
}
