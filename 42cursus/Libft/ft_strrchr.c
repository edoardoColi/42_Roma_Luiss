/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 11:00:05 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/19 14:19:58 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
My own function implementing the original one.
For more use "man strrchr" 
*/
char	*ft_strrchr(const char *s, int c)
{
	char	*last;		//Return value

	last = (char *)s + ft_strlen(s);
	while (*last != (unsigned char)c)
	{
		if (last == s)
			return (NULL);
		last--;
	}
	return (last);
}
