/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_gestion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:02:45 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/06 08:36:00 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**malloc_names_ii(t_struct lst, char *line, char **vars_name,
	int *x)
{
	int	lenght;
	int	tmpx;
	int	ptry;

	tmpx = x[0];
	ptry = x[1];
	if (line[tmpx++] == '$')
	{
		lenght = 0;
		while (ft_isalnum(line[tmpx]) || line[tmpx] == '?')
		{
			if (line[tmpx] != '?')
				break ;
			tmpx++;
			lenght++;
		}
		vars_name[ptry] = malloc(sizeof(char) * (lenght + 1));
		if (!vars_name[ptry++])
			error(MEM_ERR, &lst, NULL, 1);
	}
	x[0] = tmpx;
	x[1] = ptry;
	return (vars_name);
}

static char	**malloc_names(t_struct lst, char *line, char **vars_name)
{
	char	**ret;
	int		x[2];

	x[0] = 0;
	x[1] = 0;
	while (line[x[0]])
	{
		if (line[x[0]] == 39)
			x[0]++;
		else if (line[x[0]] == 34)
		{
			x[0]++;
			while (line[x[0]] && line[x[0]] != 34)
				ret = malloc_names_ii(lst, line, vars_name, &x[0]);
		}
		else
			ret = malloc_names_ii(lst, line, vars_name, &x[0]);
	}
	return (ret);
}

/*remplissage du tableau char ** variables->valeurs*/
static char	*tab_filling(t_struct lst, char *line, char **vars_name)
{
	char	*new_line;

	new_line = NULL;
	vars_name = malloc_names(lst, line, vars_name);
	vars_name = get_vars_names(line, vars_name);
	new_line = get_new_line(lst, line, vars_name);
	return (new_line);
}

/*compte le nombre de variables d'env a remplacer*/
static int	var_count(t_struct lst, char *line)
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
					return (error(QUOTE_ERR, &lst, NULL, 0));
		}
		else if (line[x] == 34)
		{
			while (line[++x] && line[x] != 34)
				if (line[x] == '$')
					ret++;
			if (!line[x])
				return (error(QUOTE_ERR, &lst, NULL, 0));
		}
		else if (line[x] == '$')
			ret++;
	}
	return (ret);
}

char	*var_gestion(t_struct lst, char *line)
{
	char	*new_line;
	char	**vars_tab;
	int		nb_vars;

	nb_vars = var_count(lst, line);
	if (nb_vars < 0)
		return (NULL);
	vars_tab = NULL;
	if (nb_vars > 0)
	{
		vars_tab = malloc(sizeof(char *) * (nb_vars + 1));
		if (!vars_tab)
		{
			free(line);
			error(MEM_ERR, &lst, NULL, 1);
		}
		vars_tab[nb_vars] = NULL;
		new_line = tab_filling(lst, line, vars_tab);
		ft_free(vars_tab);
		free(line);
		return (new_line);
	}
	return (line);
}
