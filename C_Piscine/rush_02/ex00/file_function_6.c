/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_function_6.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 21:41:06 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/12 21:41:10 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"
#include "functions.h"

int	get_righe(char *file)
{
	int		i[4];
	char	buffer;

	i[0] = 0;
	i[2] = open(file, O_RDONLY);
	i[1] = read(i[2], &buffer, SIZE_1B);
	while (i[1] > 0)
	{
		while (i[1] > 0 && buffer != '\n')
		{
			if (!is_printable(buffer))
			{
				close(i[2]);
				return (0);
			}
			i[1] = read(i[2], &buffer, SIZE_1B);
		}
		i[0]++;
		i[1] = read(i[2], &buffer, SIZE_1B);
	}
	return (i[0]);
}

void	print_num(t_nodo *diz, char *num)
{
	int	size;
	int	mod;

	size = ft_strlen(num);
	mod = size % 3;
	stampa_rec(diz, num, size, mod);
	write(out, "\n", 1);
}

void	see_diz(char *file, char *num)
{
	int		num_righe;
	char	**tab;
	t_nodo	*diz;

	num_righe = get_righe(file);
	tab = generate_file_tab(file, num_righe);
	if (!tab)
	{
		error_diz();
		libera_tab(tab, num_righe);
		return ;
	}
	diz = generate_diz(tab, num_righe);
	if (!diz)
	{
		error_diz();
		libera_tab(tab, num_righe);
		libera_diz(diz);
		return ;
	}
	print_num(diz, num);
	libera_tab(tab, num_righe);
	libera_diz(diz);
}
