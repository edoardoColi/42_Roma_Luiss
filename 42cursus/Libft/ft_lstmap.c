/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecoli <ecoli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 16:42:03 by ecoli             #+#    #+#             */
/*   Updated: 2022/03/24 11:50:53 by ecoli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
lst: The address of a pointer to a node.
f: The address of the function used to iterate on
the list.
del: The address of the function used to delete
the content of a node if needed.
Return the new list.
NULL if the allocation fails.
Iterates the list ’lst’ and applies the function
’f’ on the content of each node. Creates a new
list resulting of the successive applications of
the function ’f’. The ’del’ function is used to
delete the content of a node if needed.
*/
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head;		//Return value
	t_list	*f_lst;		//Step by step node to which function f is applied

	if (!lst)
		return (NULL);
	head = NULL;
	if (f || del)
	{
		f_lst = ft_lstnew(f(lst->content));
		head = f_lst;
		lst = lst->next;
		while (lst)
		{
			f_lst = ft_lstnew(f(lst->content));
			if (!f_lst)
			{		//Don't know exactly why we delete both
				ft_lstclear(&lst, del);
				ft_lstclear(&head, del);
				return (NULL);
			}
			lst = lst->next;
			ft_lstadd_back(&head, f_lst);
		}
	}
	return (head);
}
