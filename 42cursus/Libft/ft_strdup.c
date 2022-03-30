/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 10:58:46 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/19 14:18:38 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
My own function implementing the original one.
For more use "man strdup" 
*/
char	*ft_strdup(const char *s1)
{
	size_t	l;
	char	*cpy;		//Return value

	l = ft_strlen(s1);
	cpy = malloc(sizeof(char) * l + 1);
	if (!cpy)
		return (NULL);
	ft_memcpy(cpy, s1, l);
	cpy[l] = '\0';
	return (cpy);
}
