/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 10:25:52 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/06 09:42:06 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*clean_join(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	s1 = NULL;
	s2 = NULL;
	return (tmp);
}

char	*third_lecture_iv(char *line, char *new)
{
	int	x;
	int	y;

	x = -1;
	y = 0;
	while (line[++x])
	{
		if (line[x] == 34)
			while (line[++x] && line[x] != 34)
				new[y++] = line[x];
		else if (line[x] == 39)
			while (line[++x] && line[x] != 39)
				new[y++] = line[x];
		else
			new[y++] = line[x];
	}
	new[y] = '\0';
	free(line);
	return (new);
}

int	third_lecture_iii(char *line, int *i, int count, int opt)
{
	int	x;

	x = *i + 1;
	while (line[x] && line[x] != opt)
	{
		count++;
		x++;
	}
	*i = x;
	return (count);
}

int	third_lecture_ii(char *line, int x)
{
	int	count;

	count = 0;
	while (line[x])
	{
		if (line[x] == 34)
		{
			count = third_lecture_iii(line, &x, count, 34);
			if (!line[x++])
				return (-1);
		}
		else if (line[x] == 39)
		{
			count = third_lecture_iii(line, &x, count, 39);
			if (!line[x++])
				return (-1);
		}
		else
		{
			count++;
			x++;
		}
	}
	return (count);
}

char	*third_lecture(t_struct *lst, char *line)
{
	int		x;
	int		y;
	char	*new;

	if (!line)
		return (ft_strdup(""));
	x = 0;
	y = third_lecture_ii(line, x);
	if (y == -1)
		return (NULL);
	new = malloc(sizeof(char) * (y + 1));
	if (!new)
		error(MEM_ERR, lst, NULL, 1);
	return (third_lecture_iv(line, new));
}
