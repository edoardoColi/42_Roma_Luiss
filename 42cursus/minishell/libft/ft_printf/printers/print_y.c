/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_y.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:25:34 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 16:06:27 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../libft.h"
#include "../ft_printf.h"
#include <stdio.h>

void	print_y(t_pflags *tf)
{	
	static int	counter;
	char		*str;

	if (!counter)
		counter = 0;
	str = ft_itoa(counter);
	write(1, str, pf_strlen(str));
	write(1, ".", 1);
	tf->dimension += pf_strlen(str) + 1;
	counter++;
	free(str);
}
