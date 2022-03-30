/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eddy_0 <eddy_0@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 12:14:41 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/19 14:17:52 by eddy_0           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
lst: The beginning of the list.
Return the length of the list.
Counts the number of nodes in a list.
*/
int	ft_lstsize(t_list *lst)
{
	int		s;
	t_list	*n;

	s = 0;
	n = lst;
	while (n)
	{
		n = n->next;
		s++;
	}
	return (s);
}
