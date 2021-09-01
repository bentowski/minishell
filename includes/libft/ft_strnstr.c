/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 11:31:41 by bbaudry           #+#    #+#             */
/*   Updated: 2021/07/30 22:50:31 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	x;
	size_t	y;

	y = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[y] != '\0' && len > 0 && y <= len)
	{
		x = 0;
		while (haystack[y + x] == needle[x] && (y + x) < len)
		{
			x++;
			if (needle[x] == '\0')
				return ((char *)&haystack[y]);
		}
		y++;
	}
	return (NULL);
}
