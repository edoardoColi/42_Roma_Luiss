/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_function_5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 21:41:34 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/12 21:41:36 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"
#include "functions.h"

void	stampa_rec1(t_nodo *diz, char *num, int size)
{
	if (num[0] != '0')
	{
		stampa_num(diz, num[0] - '0', 1);
		write (1, " ", 1);
		stampa_num(diz, 1, 3);
		write (1, " ", 1);
	}
	stampa_rec(diz, num + 1, size - 1, 2);
}

void	stampa_rec2(t_nodo *diz, char *num, int size)
{
	stampa_num(diz, num[0] - '0', 1);
	if (size > 1 && num[0] != '0')
	{
		write (1, " ", 1);
		stampa_num(diz, 1, size);
		if (num[1] != '0')
			write (1, " ", 1);
	}
	stampa_rec(diz, num + 1, size - 1, 0);
}

void	stampa_rec4(t_nodo *diz, char *num, int size)
{
	if (num[0] != '0')
	{
		stampa_num(diz, (num[0] - '0') * 10, 2);
		if (size > 1)
			write (1, " ", 1);
	}
	if (num[1] != '0')
	{
		stampa_num(diz, num[1] - '0', 1);
		if (size > 2)
			write (1, " ", 1);
	}
}

void	stampa_rec3(t_nodo *diz, char *num, int size)
{
	if (num[0] != '1')
	{
		stampa_rec4(diz, num, size);
	}
	else
	{
		if (num[0] != '0' || num[1] != '0')
			stampa_num(diz, (num[0] - '0') * 10 + num[1] - '0', 2);
		if (size > 2 && num[0] != '0')
			write (1, " ", 1);
	}
	if (size >= 4 && num[-1] != '0')
	{
		stampa_num(diz, 1, size - 1);
		write (1, " ", 1);
	}
	stampa_rec(diz, num + 2, size - 2, 0);
}

void	stampa_rec(t_nodo *diz, char *num, int size, int mod)
{
	if (size <= 0)
		return ;
	if (mod == 0)
		stampa_rec1(diz, num, size);
	else if (mod == 1)
		stampa_rec2(diz, num, size);
	else
		stampa_rec3(diz, num, size);
}
