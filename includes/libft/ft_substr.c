/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 11:53:10 by bbaudry           #+#    #+#             */
/*   Updated: 2021/07/30 23:03:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	x;
	char			*d;

	x = 0;
	if (!s)
		return (NULL);
	d = malloc(sizeof(char) * (len + 1));
	if (!(d))
		return (NULL);
	while (s[x + start] && x < len && (x + start) < (unsigned int)ft_strlen(s))
	{
		d[x] = s[x + start];
		x++;
	}
	d[x] = '\0';
	return (d);
}
