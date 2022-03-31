/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_perc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:57:20 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/31 13:33:57 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
perc: The character %
count: Reference to the printed character counter.
Print the character and increase the counter.
*/
void	case_perc(char perc, ssize_t *count)
{
	write(out, &perc, 1);
	*count = *count + 1;
}
