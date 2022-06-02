/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_int_tab.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 11:33:52 by ecoli             #+#    #+#             */
/*   Updated: 2021/12/03 11:54:22 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include<stdio.h>

void	swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	quicksort(int *arr, int primo, int ultimo)
{
	int	i;
	int	j;
	int	pivot;

	if (primo < ultimo)
	{
		pivot = ultimo;
		i = primo;
		j = ultimo;
		while (i < j)
		{
			while (arr[i] <= arr[pivot] && i < ultimo)
				i++;
			while (arr[j] > arr[pivot])
				j--;
			if (i < j)
			{
				swap(&arr[i], &arr[j]);
			}
		}
		swap(&arr[pivot], &arr[j]);
		quicksort(arr, primo, j - 1);
		quicksort(arr, j + 1, ultimo);
	}
}

void	ft_sort_int_tab(int *tab, int size)
{
	quicksort(tab, 0, size - 1);
}
