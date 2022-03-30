/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:53:08 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/19 14:16:20 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
My own function implementing the original one.
For more use "man calloc" 
*/
void	*ft_calloc(size_t count, size_t size)
{
	void	*a;
	size_t	space;

	space = count * size;
	a = malloc(space);
	if (!a)
		return (NULL);
	ft_memset(a, 0, space);
	return (a);
}
