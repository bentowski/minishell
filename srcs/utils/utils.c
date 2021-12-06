/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 10:25:52 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/05 21:54:36 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_env(char *str, char **env)
{
	int	i;
	int	x;
	int	y;

	i = -1;
	while (env[++i])
	{
		x = ft_strchr(env[i], '=') - env[i];
		y = ft_strlen(str);
		if (x < y)
			x = y;
		if (ft_strncmp(str, env[i], x) == 0)
			return (ft_strdup(&env[i][ft_strlen(str) + 1]));
	}
	return (NULL);
}

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

char	*third_lecture(char *line)
{
	int		x;
	int		y;
	int		count;
	char	*new;

	if (!line)
		return (ft_strdup(""));
	x = 0;
	count = 0;
	while (line[x])
	{
		if (line[x] == 34)
		{
			x++;
			while (line[x] && line[x] != 34)
			{
				count++;
				x++;
			}
			if (!line[x])
				return (NULL);
			x++;
		}
		else if (line[x] == 39)
		{
			x++;
			while (line[x] && line[x] != 39)
			{
				count++;
				x++;
			}
			if (!line[x])
				return (NULL);
			x++;
		}
		else
		{
			count++;
			x++;
		}
	}
	new = malloc(sizeof(char) * (count + 1));
	if (!new)
		return (NULL);
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

