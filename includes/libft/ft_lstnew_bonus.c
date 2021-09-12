/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 13:50:48 by bbaudry           #+#    #+#             */
/*   Updated: 2021/09/11 15:48:27 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(char *content, int infile, int outfile)
{
	t_list	*lst;

	lst = NULL;
	lst = malloc(sizeof(t_list));
	if (!(lst))
		return (NULL);
	lst->content = malloc(sizeof(char) * (ft_strlen(content) + 1));
	ft_strlcpy(lst->content, content, ft_strlen(content) + 1);
	lst->file[0] = infile;
	lst->file[1] = outfile;
	lst->next = NULL;
	return (lst);
}
