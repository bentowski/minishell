/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_gestion3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 08:34:53 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/06 08:36:29 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_new_line_iii(t_struct lst,
		char *vars_name, char **trash, int *i)
{
	int		x;
	int		y;
	int		z;
	char	*tmp;

	x = i[0] + 1;
	y = i[1];
	z = 0;
	if (trash[0][x] == '?')
	{
		tmp = v_itoa(lst.exit_status);
		x++;
	}
	else
		tmp = ft_get_env(vars_name, *lst.env);
	if (tmp)
		while (tmp[z])
			trash[1][y++] = tmp[z++];
	while (ft_isalnum(trash[0][x]) || trash[0][x] == '_')
		x++;
	i[0] = x;
	i[1] = y;
	free(tmp);
	return (trash[1]);
}

//trash[0] = line
//trash[1] = new;
static char	*get_new_line_ii(t_struct lst, char **trash,
		char **vars_name, int l)
{
	int	x[2];

	x[0] = 0;
	x[1] = 0;
	while (trash[0][x[0]])
	{
		if (trash[0][x[0]] == 39)
			trash[1][x[1]++] = trash[1][x[0]++];
		else if (trash[0][x[0]] == 34)
		{
			trash[1][x[1]++] = trash[0][x[0]++];
			while (trash[0][x[0]] && trash[0][x[0]] != 34)
				if (trash[0][x[0]] == '$')
					trash[1] = get_new_line_iii(lst, vars_name[l++], trash, x);
			else
				trash[1][x[1]++] = trash[0][x[0]++];
			trash[1][x[1]++] = trash[0][x[0]++];
		}
		else if (trash[0][x[0]] == '$')
			trash[1] = get_new_line_iii(lst, vars_name[l++], trash, x);
		else
			trash[1][x[1]++] = trash[0][x[0]++];
	}
	trash[1][x[1]] = '\0';
	return (trash[1]);
}

char	*get_new_line(t_struct lst, char *line, char **vars_name)
{
	int		lenght;
	char	*new;
	char	*trash[2];

	lenght = get_new_lenght(lst, line, vars_name, *lst.env);
	if (!lenght)
		return (NULL);
	new = malloc(sizeof(char) * (lenght + 1));
	if (!new)
		error(MEM_ERR, &lst, NULL, 1);
	trash[0] = line;
	trash[1] = new;
	return (get_new_line_ii(lst, trash, vars_name, 0));
}
