/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_function_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 17:41:12 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/12 18:20:34 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"
#include "functions.h"

char	**generate_file_tab(char *file, int num_righe)
{
	int		i;
	int		len_righe;
	char	**tab;

	len_righe = 1000;
	i = 0;
	tab = malloc(sizeof(*tab) * num_righe);
	if (!tab)
	{
		return (0);
	}
	while (i < num_righe)
	{
		tab[i] = malloc(sizeof(**tab) * len_righe);
		if (!tab[i])
			return (0);
		i++;
	}
	tab = fill_tab(file, tab);
	return (tab);
}

t_nodo	*generate_diz(char **table, int num_righe)
{
	int		i;
	int		key;
	int		decine;
	t_nodo	*diz;

	i = 0;
	diz = 0;
	while (i < num_righe)
	{
		key = my_atoi2(table[i], &decine);
		diz = agg_ordinato_unico(key, decine, nome_key(table[i]), diz);
		i++;
	}
	return (diz);
}

t_nodo	*agg_ordinato_unico2(int num, int decine, char *nome, t_nodo *succ)
{
	t_nodo	*nuovo;

	nuovo = malloc(sizeof(t_nodo));
	nuovo->next = succ;
	nuovo->valore = num;
	nuovo->decine = decine;
	nuovo->nome = nome;
	succ = nuovo;
	return (succ);
}

t_nodo	*agg_ordinato_unico(int num, int decine, char *nome, t_nodo *succ)
{
	if (succ == 0)
		return (agg_ordinato_unico2(num, decine, nome, succ));
	else
	{
		if (decine >= succ->decine)
		{
			if (succ->valore == num && succ->decine == decine)
			{
				return (succ);
			}
			else
			{
				return (agg_ordinato_unico2(num, decine, nome, succ));
			}
		}
		else
		{
			succ->next = agg_ordinato_unico(num, decine, nome, succ->next);
			return (succ);
		}
	}
}

int	my_atoi2(char *str, int *ord)
{
	int	i;
	int	n;
	int	decine;

	decine = 0;
	i = 0;
	n = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 48 && str[i] <= 57)
		{
			if (n < 21474836)
				n = n * 10 + (str[i] - '0');
			decine++;
		}
		else
		{
			*ord = decine;
			return (my_atoi2_2(n));
		}
		i++;
	}
	*ord = decine;
	return (my_atoi2_2(n));
}
