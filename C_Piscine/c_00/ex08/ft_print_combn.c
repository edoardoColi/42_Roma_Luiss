/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_combn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 19:58:27 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/01 20:26:50 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_print_arr(int arr[], int n)
{
	int	i;

	i = 0;
	write(1, ", ", 2);
	while (i < n)
	{
		ft_putchar(arr[i] + '0');
		i++;
	}
}

int	ft_end_arr(int arr[], int n)
{
	int	i;
	int	oversize;

	i = 0;
	oversize = 0;
	if (n == 1)
		return (0);
	while (arr[i] != 10 - n + i && oversize == 0)
	{
		i++;
		if (i > n)
			oversize = 1;
	}
	if (!oversize)
	{
		arr[i -1]++;
		while (i < n)
		{
			arr[i] = arr[i -1] +1;
			i++;
		}
	}
	return (1);
}

void	ft_start_arr(int arr[], int n)
{
	int	i;

	i = 0;
	while (i < 9)
	{
		arr[i] = i;
		if (i < n)
			ft_putchar(arr[i] + '0');
	i++;
	}
}

void	ft_print_combn(int n)
{
	int	arr[9];
	int	j;
	int	k;

	j = 0;
	k = 0;
	if (n > 9 || n < 0)
		return ;
	ft_start_arr(arr, n);
	while (arr[0] != 10 - n)
	{
		while (arr[n -1] != 9)
		{
			arr[n -1]++;
			ft_print_arr(arr, n);
		}
		if (ft_end_arr(arr, n))
			ft_print_arr(arr, n);
	}
}
