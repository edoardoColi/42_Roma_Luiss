/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   case_char.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 13:56:38 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/31 13:30:52 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
c: The character to print.
count: Reference to the printed character counter.
Print the character and increase the counter.
*/
void	case_char(int c, ssize_t *count)
{
	unsigned char	uc;

	uc = (unsigned char) c;		//I don't think it's strictly necessary
	write(out, &uc, 1);
	*count = *count + 1;
}
