/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_gestion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:02:45 by bbaudry           #+#    #+#             */
/*   Updated: 2021/11/30 17:53:46 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../errors/errors.h"

static int	get_new_lenght(t_struct lst, char *line, char **vars_name,
	char **env)
{
	int	lenght;
	int	x;

	x = -1;
	lenght = 0;
	while (vars_name[++x])
	{
		if (ft_get_env(vars_name[x], env))
			lenght += ft_strlen(ft_get_env(vars_name[x], env));
		else if (ft_strncmp(vars_name[x], "?", 2) == 0)
			return (ft_strlen(get_exit_status(&lst)));
		else
			return (0);
	}
	x = 0;
	while (line[x])
	{
		if (line[x] == 39)
			x++;
		else if (line[x] == 34)
		{
			while (line[++x] && line[x] != 34)
				lenght++;
			x++;
		}
		else
			lenght++;
		x++;
	}
	return (lenght);
}

static char *third_lecture(char *line)
{
	int x;
	int y;
	int count;
	char *new;

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
	return (new);
}

static char	*get_new_line(t_struct lst, char *new, char *line, char **vars_name)
{
	char	*tmp;
	char	*tmp2;
	int		x;
	int		y;
	int		i;
	int		lenght;

	x = 0;
	y = 0;
	tmp2 = NULL;
	lenght = get_new_lenght(lst, line, vars_name, *lst.env);
	if (!lenght)
	{
		error(NO_VAR, &lst, NULL, 0);
		return (NULL);
	}
	new = malloc(sizeof(char) * lenght);
	if (!new)
		error(MEM_ERR, &lst, NULL, 1);
	lenght = 0;
	while (line[x])
	{
		if (line[x] == 39)
			x++;
		if (line[x] == 34)
		{
			x++;
			while (line[x] && line[x] != 34)
			{
				if (line[x] == '$')
				{
					i = 0;
					if (line[x + 1] == '?')
						tmp2 = get_exit_status(&lst);
					else
					{
						tmp = ft_get_env(vars_name[lenght++], *lst.env);
						tmp2 = third_lecture(tmp);
					}
					if (tmp2)
					{
						while (tmp2[i])
							new[y++] = tmp2[i++];
					}
					x++;
					while (ft_isalnum(line[x]))
						x++;
				}
				else
					new[y++] = line[x++];
			}
			x++;
		}
		else if (line[x] == '$')
		{
			i = 0;
			if (line[x + 1] == '?')
			{
				x++;
				tmp2 = get_exit_status(&lst);
			}
			else
			{
				tmp = ft_get_env(vars_name[lenght++], *lst.env);
				tmp2 = third_lecture(tmp);
				x++;
				while (ft_isalnum(line[x]))
					x++;
			}
			x++;
			if (tmp2)
			{
				while (tmp2[i])
					new[y++] = tmp2[i++];
			}
		}
		else
			new[y++] = line[x++];
		if (tmp2)
		{
			free(tmp2);
			tmp2 = NULL;
		}
	}
	new[y] = '\0';
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
	while (ft_isalnum(line[x]))
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
						vars_name[y] = "?";
					else
						vars_name[y] = get_vars_names_ii(line, vars_name[y], &x);
					y++;
				}
			}
		}
		else if (line[x++] == '$')
		{
			if (line[x] == '?')
				vars_name[y] = "?";
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
		if (line[tmpx++] != '?')
			while (ft_isalnum(line[tmpx++]))
				lenght++;
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
		printf("%s\n", "OK");
		free(line);
		return (new_line);
	}
	return (line);
}
