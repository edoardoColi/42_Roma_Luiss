/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy <eddy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 23:15:35 by ecoli             #+#    #+#             */
/*   Updated: 2023/04/16 14:22:46 by eddy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// src and dest must be null terminated!!
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	c;
	size_t	i;
	size_t	s;
	size_t	cs;

	cs = ft_strlen(dst);
	s = ft_strlen(src);
	c = cs;
	i = 0;
	if (cs > dstsize)
		cs = dstsize;
	if (cs < (dstsize - 1) && dstsize > 0)
	{
		while (src[i] && (cs + i < dstsize - 1))
		{
			dst[c] = src[i];
			c++;
			i++;
		}
		dst[c] = 0;
	}
	return (cs + s);
}
