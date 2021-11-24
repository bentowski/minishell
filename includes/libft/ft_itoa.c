/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 11:51:33 by bbaudry           #+#    #+#             */
/*   Updated: 2021/11/24 15:45:35 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

static unsigned int	ft_size(unsigned int n)
{
	unsigned int	size;

	size = 0;
	n = ft_abs(n);
	while (n / 10 > 0)
	{
		n /= 10;
		size++;
	}
	return (size + 1);
}

static unsigned char	*boucle_norme(int nb, int size, unsigned char **str)
{
	while (nb > 0)
	{
		*str[size - 1] = nb % 10 + '0';
		nb /= 10;
		size--;
	}
	return (*str);
}

char	*ft_itoa(int n)
{
	unsigned char	*str;
	unsigned int	nb;
	unsigned int	size;

	nb = ft_abs(n);
	if (n < 0)
		size = ft_size(nb) + 2;
	else
		size = ft_size(nb) + 1;
	str = (unsigned char *)malloc(size);
	if (!(size))
		return (0);
	str[size - 1] = '\0';
	if (n == 0)
		str[0] = '0';
	else
	{
		if (n < 0)
			str[0] = '-';
		boucle_norme(nb, size, &str);
	}
	return ((char *)str);
}
