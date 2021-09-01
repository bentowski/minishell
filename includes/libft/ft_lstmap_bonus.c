/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 15:48:29 by bbaudry           #+#    #+#             */
/*   Updated: 2021/07/30 22:50:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*ptr;
	t_list	*new;

	if (!lst)
		return (NULL);
	if (!f)
		return ((t_list *)lst);
	new = ft_lstnew(f(lst->content));
	if (!(new))
		return (NULL);
	ptr = new;
	while (lst->next)
	{
		lst = lst->next;
		new->next = ft_lstnew(f(lst->content));
		if (!(new->next))
			ft_lstclear(&ptr, del);
		new = new->next;
	}
	return (ptr);
}
