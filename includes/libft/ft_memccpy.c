/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:18:09 by bbaudry           #+#    #+#             */
/*   Updated: 2019/10/09 14:18:30 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*psrc;
	unsigned char	*pdst;
	size_t			i;

	i = 0;
	psrc = (unsigned char *)src;
	pdst = (unsigned char *)dst;
	while (n > i)
	{
		pdst[i] = psrc[i];
		if (psrc[i] == (unsigned char)c)
			return (dst + 1 + i);
		i++;
	}
	return (0);
}
