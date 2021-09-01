/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 15:55:51 by bbaudry           #+#    #+#             */
/*   Updated: 2019/10/30 10:29:39 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			x;
	unsigned char	*ps;

	x = 0;
	ps = (unsigned char *)s;
	while (n > x)
	{
		if (ps[x] == (unsigned char)c)
			return (ps + x);
		x++;
	}
	return (NULL);
}
