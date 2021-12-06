/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_gestion2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 08:33:02 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/06 08:36:06 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_vars_names_iii(char *line, char *voidline, int *xvalue)
{
	char	*new;
	int		lenght;
	int		x;

	x = *xvalue;
	new = voidline;
	lenght = 0;
	while (ft_isalnum(line[x]) || line[x] == '_')
		new[lenght++] = line[x++];
	new[lenght] = '\0';
	*xvalue = x;
	return (new);
}

static char	**get_vars_names_ii(char *line, char **vars_name, int *i, int *j)
{
	int	x;

	x = *i;
	if (line[x] == '?')
	{
		vars_name[*j][0] = '?';
		vars_name[*j][1] = '\0';
	}
	else
		vars_name[*j] = get_vars_names_iii(line,
				vars_name[*j], &x);
	*i = x;
	*j = *j + 1;
	return (vars_name);
}

char	**get_vars_names(char *line, char **vars_name)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (line[x])
	{
		if (line[x] == 39)
			x++;
		else if (line[x] == 34)
		{
			x++;
			while (line[x] && line[x] != 34)
			{
				if (line[x++] == '$')
					vars_name = get_vars_names_ii(line, vars_name, &x, &y);
			}
		}
		else if (line[x++] == '$')
			vars_name = get_vars_names_ii(line, vars_name, &x, &y);
	}
	return (vars_name);
}
