/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 01:39:10 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/06 11:23:24 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_quotes_good(t_struct *lst, char *line)
{
	int	x;
	int	ret;

	x = -1;
	ret = 0;
	while (line[++x])
	{
		if (line[x] == 39)
		{
			while (line[++x] != 39)
				if (!line[x])
					return (error(QUOTE_ERR, lst, NULL, 0));
		}
		else if (line[x] == 34)
		{
			while (line[++x] && line[x] != 34)
				if (line[x] == '$')
					ret++;
			if (!line[x])
				return (error(QUOTE_ERR, lst, NULL, 0));
		}
		else if (line[x] == '$')
			ret++;
	}
	return (0);
}

int	check_pipes_good(t_struct *lst, char *line)
{
	int	x;
	int	ret;

	x = 0;
	ret = 0;
	while ((line[x] == '\t' || line[x] == '\n' || line[x] == '\r'
			|| line[x] == '\v' || line[x] == '\f'))
		x++;
	if (line[x] == '|')
		return (error(LON_PIPE, lst, NULL, 0));
	while (line[x])
	{
		if (line[x] == '|')
		{
			x++;
			while ((line[x] == '\t' || line[x] == '\n' || line[x] == '\r'
					|| line[x] == '\v' || line[x] == '\f'))
				x++;
			if (!line[x])
				return (error(LON_PIPE, lst, NULL, 0));
		}
		x++;
	}
	return (check_quotes_good(lst, line));
}
