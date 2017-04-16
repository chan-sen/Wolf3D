/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chansen <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/08 13:33:17 by chansen           #+#    #+#             */
/*   Updated: 2016/10/08 13:33:18 by chansen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*newlst;
	t_list		*head;

	if (!lst)
		return (NULL);
	if (!(head = ft_lstnew(lst->content, lst->content_size)))
		return (NULL);
	head = f(lst);
	newlst = head;
	while (lst->next)
	{
		newlst->next = f(lst->next);
		newlst = newlst->next;
		lst = lst->next;
	}
	return (head);
}
