/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_space.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <vgallois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 14:14:44 by vgallois          #+#    #+#             */
/*   Updated: 2021/12/06 08:28:59 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	_nb_space(char *s)
{
	int	len;

	len = 0;
	while (*s)
	{
		if (*s == '<' || *s == '>')
			len += 2;
		if (*s == '|')
			len += 2;
		s++;
	}
	return (len);
}

static void	_skip_doublequote(char *res, char *s, int *x, int *y)
{
	int	i;
	int	j;

	i = *x;
	j = *y;
	res[j++] = s[i++];
	while (s[i] != '"')
		res[j++] = s[i++];
	res[j++] = s[i++];
	*x = i;
	*y = j;
}

static void	_redir(char *res, char *s, int *x, int *y)
{
	int	i;
	int	j;

	i = *x;
	j = *y;
	res[j++] = ' ';
	res[j++] = s[i++];
	if (s[i] == '<' || s[i] == '>')
		res[j++] = s[i++];
	if (s[i + 1] != '<' && s[i + 1] != '>')
		res[j++] = ' ';
	*x = i;
	*y = j;
}

static void	_pipes(char *res, char *s, int *x, int *y)
{
	int	i;
	int	j;

	i = *x;
	j = *y;
	res[j++] = ' ';
	res[j++] = s[i++];
	res[j++] = ' ';
	*x = i;
	*y = j;
}

char	*add_space(t_struct lst, char *s)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	len = _nb_space(s) + ft_strlen(s);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
	{
		error(MEM_ERR, &lst, NULL, 0);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '"')
			_skip_doublequote(res, s, &i, &j);
		else if (s[i] == '\'')
			skip_quote(res, s, &i, &j);
		else if (s[i] == '<' || s[i] == '>')
			_redir(res, s, &i, &j);
		else if (s[i] == '|')
			_pipes(res, s, &i, &j);
		else
			res[j++] = s[i++];
	}
	res[j] = 0;
	free(s);
	return (res);
}
