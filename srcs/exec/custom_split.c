/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <vgallois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:17:06 by vgallois          #+#    #+#             */
/*   Updated: 2021/12/05 02:53:05 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	_get_len_split(char *s)
{
	int	i;
	int	n;

	n = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '"')
		{
			while (s[++i] != '"')
				;
		}
		if (s[i] == '\'')
		{
			while (s[++i] != '\'')
				;
		}
		if (s[i] == ' ')
			n++;
		i++;
	}
	return (n);
}

static int	_find_next_sp(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '"')
			while (s[++i] != '"')
				;
		if (s[i] == '\'')
		{
			while (s[++i] != '\'')
				;
		}
		if (s[i] == ' ')
			return (i);
		i++;
	}
	return (i);
}

static char	*_get_next_part(t_struct *lst, char *s, char **tab)
{
	int		len;
	char	*res;
	int		i;

	len = _find_next_sp(s);
	res = malloc(sizeof(char) *(len + 1));
	if (!res)
	{
		ft_free(tab);
		error(MEM_ERR, lst, NULL, 1);
	}
	i = -1;
	while (++i < len)
		res[i] = s[i];
	res[i] = 0;
	return (res);
}

char	**custom_split(char *s, t_struct *lst)
{
	int		nb;
	char	**res;
	int		i;
	int		j;

	i = 0;
	j = 0;
	nb = _get_len_split(s) + 1;
	res = malloc(sizeof(char *) * (nb + 1));
	if (!res)
		error(MEM_ERR, lst, NULL, 1);
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i])
		{
			res[j++] = _get_next_part(lst, s + i, res);
			i += _find_next_sp(s + i);
		}
	}
	res[j] = NULL;
	return (res);
}
