/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_function5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebondi <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 18:20:45 by ebondi            #+#    #+#             */
/*   Updated: 2021/12/14 18:26:09 by ebondi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include "functions.h"

int	check_first_line(char	*file, int len_r1, int *num_righe, char *ebf)
{
	int		i[4];
	char	buffer;
	char	*line;

	i[2] = 0;
	i[3] = 0;
	i[0] = open(file, O_RDONLY);
	i[1] = read(i[0], &buffer, SIZE_1B);
	line = malloc(sizeof(char) * len_r1 + 1);
	if (!line)
		return (libera1(0, i[0], 0));
	while (i[1] > 0)
	{
		while (i[1] > 0 && buffer != '\n')
		{
			line[i[2]] = buffer;
			i[2]++;
			i[1] = read(i[0], &buffer, SIZE_1B);
		}
		if (!i[3])
		{
			line[i[2]] = '\0';
			if (!parse_first_line(line, ebf, num_righe))
				return (libera1(0, i[0], line));
		}
		break ;
		i[1] = read(i[0], &buffer, SIZE_1B);
	}
	return (libera1(1, i[0], line));
}

int	first_look(char *file, int *len_r, char *ebf)
{
	int		i[7];
	char	buffer;

	i[5] = 0;
	i[6] = 0;
	i[3] = 0;
	i[4] = 0;
	i[2] = 0;
	i[1] = open(file, O_RDONLY);
	i[0] = read(i[1], &buffer, SIZE_1B);
	while (i[0] > 0)
	{
		while (i[0] > 0 && buffer != '\n')
		{
			if (!is_printable(buffer))
			{
				close(i[1]);
				return (0);
			}
			if (i[3] == 0)
				i[2]++;
			i[5]++;
			i[0] = read(i[1], &buffer, SIZE_1B);
		}
		if (i[4] == 1 && i[3] > 0 && i[3] != i[5])
		{
			close(i[1]);
			return (0);
		}
		if (i[3] > 0)
			i[4] = 1;
		i[3] = i[5];
		i[5] = 0;
		i[6]++;
		i[0] = read(i[1], &buffer, SIZE_1B);
	}
	*len_r = i[3];
	i[6]--;
	if (!check_first_line(file, i[2], &i[6], ebf))
		return (-1);
	close(i[1]);
	return (i[6]);
}

int	**riempi_tab(char *file, char *ebf, int num_righe, int len_righe)
{
	int		i;
	int		j;
	int		n;
	int		fd;
	char	buffer;
	int		**tab;

	tab = crea_tab(len_righe, num_righe);
	if (!tab)
		return (0);
	i = 0;
	fd = open(file, O_RDONLY);
	n = read(fd, &buffer, SIZE_1B);
	while (n > 0)
	{
		j = 1;
		while (n > 0 && buffer != '\n')
		{
			if (i != 0)
			{
				if (!(trasforma(buffer, ebf) < 0))
					tab[i][j] = trasforma(buffer, ebf);
				else
					return (chiudi(0, fd));
			}
			j++;
			n = read(fd, &buffer, SIZE_1B);
		}
		i++;
		n = read(fd, &buffer, SIZE_1B);
	}
	return (chiudi(tab, fd));
}
