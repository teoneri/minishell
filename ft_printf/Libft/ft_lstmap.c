/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneri <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:11:33 by mneri             #+#    #+#             */
/*   Updated: 2022/10/12 13:11:35 by mneri            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlist;
	t_list	*first;

	if (!f || !del)
		return (NULL);
	first = NULL;
	while (lst)
	{
		newlist = ft_lstnew((*f)(lst -> content));
		if (!newlist)
		{
			while (first)
			{
				newlist = first->next;
				(*del)(first->content);
				free(first);
				first = newlist;
			}
			lst = NULL;
			return (NULL);
		}
		ft_lstadd_back(&first, newlist);
		lst = lst -> next;
	}
	return (first);
}
