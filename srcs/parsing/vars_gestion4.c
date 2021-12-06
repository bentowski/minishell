/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_gestion4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 08:35:35 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/06 15:36:59 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_error;

static int	_connard(char *s)
{
	if (s)
		free(s);
	return (1);
}

static void	get_new_lenght_ii(char *line, int x, int *lenght)
{
	while (line[x])
	{
		if (line[x] == 39)
		{
			*lenght = *lenght + 1;
			x++;
		}
		else if (line[x] == 34)
		{
			x++;
			while (line[x] && line[x] != 34)
				if (line[++x] == '$')
					while (ft_isalnum(line[x]) || line[x] == '_')
						x++;
			else if (line[x])
				*lenght = *lenght + 1;
			*lenght = *lenght + 2;
		}
		else
			if (line[x] == '$')
				while (ft_isalnum(line[++x]) || line[x] == '_')
					;
		else if (line[x++])
			*lenght = *lenght + 1;
	}
}

int	get_new_lenght(char *line, char **vars_name, char **env)
{
	int		lenght;
	int		x;
	char	*tmp;

	lenght = 0;
	x = 0;
	get_new_lenght_ii(line, x, &lenght);
	x = -1;
	while (vars_name[++x])
	{
		tmp = ft_get_env(vars_name[x], env);
		if (tmp)
		{
			lenght += ft_strlen(tmp);
			free(tmp);
		}
		else if (_connard(tmp) && ft_strncmp(vars_name[x], "?", 2) == 0)
		{
			tmp = v_itoa(g_error);
			lenght += ft_strlen(tmp);
			free(tmp);
		}
	}
	return (lenght);
}
