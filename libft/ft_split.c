/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 11:52:51 by bbaudry           #+#    #+#             */
/*   Updated: 2021/07/30 23:15:41 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_tab(char **tab)
{
	int	n;

	n = 0;
	while (tab[n++])
		free(tab[n]);
	free(tab);
	return (NULL);
}

static char	**next_tab(char **tab, char *new_ln)
{
	int		n;
	char	**next_tab;

	n = 0;
	while (tab[n])
		n++;
	next_tab = ft_calloc(sizeof(char **), n + 2);
	if (!(next_tab))
		return (NULL);
	n = 0;
	while (tab[n])
	{
		next_tab[n] = tab[n];
		n++;
	}
	free(tab);
	next_tab[n] = new_ln;
	next_tab[n + 1] = NULL;
	return (next_tab);
}

static char	*get_ln(char const *s, size_t *i, char c)
{
	char	*str;
	int		n;

	n = 0;
	while (s[*i + n] && s[*i + n] != c)
		n++;
	str = ft_calloc(sizeof(char), n + 1);
	if (!(str))
		return (NULL);
	n = 0;
	while (s[*i + n] && s[*i + n] != c)
	{
		str[n] = s[*i + n];
		n++;
	}
	str[n] = '\0';
	*i = *i + n;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	char	**tab;
	char	*new_ln;

	tab = ft_calloc(sizeof(char **), 1);
	if (!s || !(tab))
		return (NULL);
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			new_ln = get_ln(s, &i, c);
			if (!(new_ln))
			{
				free_tab(tab);
				return (NULL);
			}
			tab = next_tab(tab, new_ln);
		}
	}
	return (tab);
}
