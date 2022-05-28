/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 13:28:17 by ecoli             #+#    #+#             */
/*   Updated: 2022/05/28 02:30:25 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "global.h"
#include "functions.h"

/*
*/
int	main(int argc, char *argv[])
{
	long	*listA;
	long	*listB;
	int		num;

	if (argc == 2)
	{
		num = counter(argv[1], ' ');
		if (num == 0)
			exit(1);
		listA = malloc(sizeof(long) * num);
		if (!listA)
			free_and_error_exit("Malloc fail", 0, 0);
		listB = malloc(sizeof(long) * num);
		if (!listB)
			free_and_error_exit("Malloc fail", listA, 0);
		fill_from_str(num, argv[1], listA, listB);
		push_swap(num, listA, listB);
	}
	if (argc > 2)
	{
		listA = malloc(sizeof(long) * argc - 1);
		if (!listA)
			free_and_error_exit("Malloc fail", 0, 0);
		listB = malloc(sizeof(long) * argc - 1);
		if (!listB)
			free_and_error_exit("Malloc fail", listA, 0);
		fill_from_args(argc - 1, argv, listA, listB);
		push_swap(argc - 1, listA, listB);
	}
	if (argc < 2)
		return (0);
	free_and_ifneeded_exit(false, listA, listB, 0);
	return (0);
}

/*
dim: Size of the list.
str: String from where to get the initial values.
listA: Reference of the list to be filled.
listB: Reference of the list to be filled.
Fills list A and B with initial values.
*/
void	fill_from_str(int dim, char *str, long listA[], long listB[])
{
	int		i;
	char	**split;

	split = ft_split(str, ' ');
	if (split == NULL)
		free_and_error_exit("Split fail", listA, listB);
	i = 0;
	while (split[i] != NULL)
	{
		listA[i] = to_int(split, i, listA, listB);
		listB[i] = 0;
		free(split[i]);									//Free the split malloc
		i++;
	}
	free(split);										//Free the split malloc
	if (!unicity(dim, listA))							//It can only be used at the beginning when list A is full
		free_and_error_exit("Some arguments are duplicates", listA, listB);
}

/*
dim: Size of the list.
args: Array of strings from where it gets the initial values.
listA: Reference of the list to be filled.
listB: Reference of the list to be filled.
Fills list A and B with initial values.
*/
void	fill_from_args(int dim, char **args, long listA[], long listB[])
{
	int	i;

	i = 0;
	while (i < dim)
	{
		listA[i] = to_int(args, i + 1, listA, listB);
		listB[i] = 0;
		i++;
	}
	if (!unicity(dim, listA))							//It can only be used at the beginning when list A is full
		free_and_error_exit("Some arguments are duplicates", listA, listB);
}

/*
error: Error string.
listA: List A of integers.
listB: List B of integers.
Prints the error message and frees the memory allocated for lists A and B.
*/
void	free_and_error_exit(char *error, long *listA, long *listB)
{
	int	l;
	int	explain;											//To enable printing of the custom error message

	explain = true;
	l = 0;
	if (listA)
		free(listA);
	if (listB)
		free(listB);
	write(err, "Error\n", 6);
	if (error && explain == true)
	{
		write(err, "-> ", 3);
		while (error[l] != '\0')
		{
			write(err, &error[l], 1);
			l++;
		}
		write(err, "\n", 1);
	}
	exit(1);
}

/*
esc: Boolean in case of forced exit.
listA: List of integers.
listB: List of integers.
listC: List of integers.
Frees the past list and exits in case.
*/
void	free_and_ifneeded_exit(int esc, long *listA, long *listB, long *listC)
{
	if (listA)
		free(listA);
	if (listB)
		free(listB);
	if (listC)
		free(listC);
	if (esc)
		exit(1);
}