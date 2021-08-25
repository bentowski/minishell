/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 16:00:22 by bbaudry           #+#    #+#             */
/*   Updated: 2020/03/12 23:30:56 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const char *s)
{
	int	x;

	x = 0;
	while (s[x] && s[x] != '\n')
	{
		x++;
	}
	return (x);
}

char	*ft_strjoin(char *s1, char *s2, int opt)
{
	char	*d;
	int		len;
	int		i;
	int		y;

	i = 0;
	y = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	d = (char *)malloc(len);
	if (!(d))
		return (NULL);
	while (s1[i] && s1[i] != '\n')
	{
		d[i] = s1[i];
		i++;
	}
	while (s2[y] && s2[y] != '\n')
		d[i++] = s2[y++];
	d[i] = '\0';
	if (opt == 2)
		free(s1);
	return (d);
}
