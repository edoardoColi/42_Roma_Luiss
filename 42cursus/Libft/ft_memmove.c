/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:57:44 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/24 11:53:53 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
My own function implementing the original one.
For more use "man memmove" 
*/
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*s;
	unsigned char	*d;

	if (dst != NULL || src != NULL)
	{
		s = (unsigned char *)src;
		d = (unsigned char *)dst;
		if (d >= s)
		{
			while (len)
			{
				len--;
				d[len] = s[len];
			}
		}
		else
			ft_memcpy(dst, src, len);
	}
	return (dst);
}
