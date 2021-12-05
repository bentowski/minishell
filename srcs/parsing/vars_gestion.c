/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_gestion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:02:45 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/05 04:14:31 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			x++;
		else if (line[x] == 34)
		{
			x++;
			while (line[x] && line[x] != 34)
			{
				if (line[x] == '$')
					while (ft_isalnum(line[++x]) || line[x] == '_')
						;
				else if (line[x++])
					*lenght = *lenght + 1;
			}
		}
		else
		{
			if (line[x] == '$')
				while (ft_isalnum(line[++x]) || line[x] == '_')
					;
			else if (line[x++])
				*lenght = *lenght + 1;
		}
	}
}

static int	get_new_lenght(t_struct lst, char *line, char **vars_name,
	char **env)
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
			lenght += ft_strlen(v_itoa(lst.exit_status));
	}
	return (lenght);
}

static char	*get_new_line(t_struct lst, char *new, char *line, char **vars_name)
{
	char	*tmp;
	int		x;
	int		y;
	int		i;
	int		lenght;

	x = 0;
	y = 0;
	lenght = get_new_lenght(lst, line, vars_name, *lst.env);
	if (!lenght)
		return (NULL);
	new = malloc(sizeof(char) * (lenght + 1));
	if (!new)
		error(MEM_ERR, &lst, NULL, 1);
	lenght = 0;
	while (line[x])
	{
		if (line[x] == 39)
			x++;
		else if (line[x] == 34)
		{
			x++;
			while (line[x] && line[x] != 34)
			{
				if (line[x] == '$')
				{
					x++;
					i = 0;
					if (line[x] == '?')
					{
						tmp = v_itoa(lst.exit_status);
						x++;
					}
					else
						tmp = ft_get_env(vars_name[lenght++], *lst.env);
					if (tmp)
						while (tmp[i])
							new[y++] = tmp[i++];
					while (ft_isalnum(line[x]) || line[x] == '_')
						x++;
				}
				else
					new[y++] = line[x++];
			}
			x++;
		}
		else if (line[x] == '$')
		{
			x++;
			i = 0;
			if (line[x] == '?')
			{
				tmp = v_itoa(lst.exit_status);
				x++;
			}
			else
			{
				tmp = ft_get_env(vars_name[lenght++], *lst.env);
				while (ft_isalnum(line[x]) || line[x] == '_')
					x++;
			}
			if (tmp)
				while (tmp[i])
					new[y++] = tmp[i++];
		}
		else
			new[y++] = line[x++];
	}
	new[y] = '\0';
	free(tmp);
	return (new);
}

static char	*get_vars_names_ii(char *line, char *voidline, int *xvalue)
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

static char	**get_vars_names(char *line, char **vars_name)
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
				{
					if (line[x] == '?')
					{
						vars_name[y][0] = '?';
						vars_name[y][1] = '\0';
					}
					else
						vars_name[y] = get_vars_names_ii(line,
								vars_name[y], &x);
					y++;
				}
			}
		}
		else if (line[x++] == '$')
		{
			if (line[x] == '?')
			{
				vars_name[y][0] = '?';
				vars_name[y][1] = '\0';
			}
			else
				vars_name[y] = get_vars_names_ii(line, vars_name[y], &x);
			y++;
		}
	}
	return (vars_name);
}

static char	**malloc_names_ii(t_struct lst, char *line, char **vars_name,
	int *x)
{
	int	lenght;
	int	tmpx;
	int	ptry;

	tmpx = x[0];
	ptry = x[1];
	if (line[tmpx] == '$')
	{
		lenght = 0;
		tmpx++;
		if (line[tmpx] != '?')
			while (ft_isalnum(line[tmpx]))
			{
				tmpx++;
				lenght++;
			}
		else
			lenght++;
		vars_name[ptry] = malloc(sizeof(char) * (lenght + 1));
		if (!vars_name[ptry++])
			error(MEM_ERR, &lst, NULL, 1);
	}
	else
		tmpx++;
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
	new_line = get_new_line(lst, new_line, line, vars_name);
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
