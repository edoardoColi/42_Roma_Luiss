/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_cptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:13:30 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 14:22:46 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_move_cptr(char **str)
{
	if (*str[0])
		(*str)++;
}

void	ft_move_n_cptr(char **str, size_t n)
{
	while (n-- > 0)
		ft_move_cptr(str);
}

// retrieve ptr position
char	**ft_reset_cptr(char **str, int status)
{
	static char	**ptr;

	if (status == 1 && ptr)
		return (ptr);
	ptr = str;
	return (NULL);
}

// store ptr position
void	ft_init_cptr(char **str)
{
	ft_reset_cptr(str, 0);
}
