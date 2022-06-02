/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 11:46:27 by tde-nico          #+#    #+#             */
/*   Updated: 2022/06/02 18:41:06 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	col_is_valid(int **tab, int *clues, int x, int size, int i)
{
	int	max_height;
	int	count;

	max_height = 0;
	count = 0;
	i = -1;
	while (++i < size)
	{
		count += tab[i][x] > max_height;
		if (tab[i][x] > max_height)
			max_height = tab[i][x];
	}
	if (count != clues[x])
		return (0);
	max_height = 0;
	count = 0;
	while (--i >= 0)
	{
		count += tab[i][x] > max_height;
		if (tab[i][x] > max_height)
			max_height = tab[i][x];
	}
	if (count != clues[x + size])
		return (0);
	return (1);
}

int	line_is_valid(int **tab, int *clues, int y, int size)
{
	int	i;
	int	max_height;
	int	count;

	max_height = 0;
	count = 0;
	i = -1;
	while (++i < size)
	{
		count += tab[y][i] > max_height;
		if (tab[y][i] > max_height)
			max_height = tab[y][i];
	}
	if (count != clues[y + size * 2])
		return (0);
	max_height = 0;
	count = 0;
	while (--i >= 0)
	{
		count += tab[y][i] > max_height;
		if (tab[y][i] > max_height)
			max_height = tab[y][i];
	}
	if (count != clues[y + size * 3])
		return (0);
	return (1);
}

int	can_put_value(int **tab, int *pos, int value, int size)
{
	int	i;

	i = -1;
	while (++i < size)
		if (tab[pos[1]][i] == value || tab[i][pos[0]] == value)
			return (0);
	return (1);
}

int	search_empty_case(int **tab, int *x, int *y, int size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = -1;
		while (++j < size)
		{
			if (tab[i][j] == 0)
			{
				*x = j;
				*y = i;
				return (1);
			}
		}
	}
	return (0);
}

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}
