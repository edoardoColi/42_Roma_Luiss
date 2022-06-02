/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/12 21:40:32 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/12 21:40:37 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush02.h"
#include "functions.h"

int	main(int argc, char *argv[])
{
	if (argc == 1)
		return (main2());
	else if (argc == 2)
		return (main3(argv[1]));
	else if (argc == 3)
	{
		if (is_valid(argv[2]) < 0)
		{
			error();
			return (1);
		}
		else
			see_diz(argv[1], argv[2]);
	}
	else
	{
		error();
		return (1);
	}
	return (0);
}

int	main2(void)
{
	char	a[1000];

	tastiera(a);
	if (is_valid(a) < 0)
	{
		error();
		return (1);
	}
	else
		see_diz("dizionario/diz.en.txt", a);
	return (0);
}

int	main3(char *a)
{
	if (is_valid(a) < 0)
	{
		error();
		return (1);
	}
	else
		see_diz("dizionario/diz.en.txt", a);
	return (0);
}

void	error(void)
{
	write(err, "Error\n", 6);
}

void	error_diz(void)
{
	write(err, "Dict Error\n", 11);
}
