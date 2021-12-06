/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:22:38 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/06 14:51:11 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	clear_env(char ***env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	free_array_content(void **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
}

void	ft_free(char **cmd_parts)
{
	int		x;
	char	**tmp;

	x = -1;
	if (!cmd_parts)
		return ;
	tmp = cmd_parts;
	while (tmp[++x])
	{
		free(tmp[x]);
		tmp[x] = NULL;
	}
	free(tmp);
	tmp = NULL;
}

void	lst_free(t_struct lst)
{
	t_list	*tmp;
	t_list	*fr;
	int		i;

	i = 0;
	tmp = lst.cmds;
	while (tmp)
	{
		fr = tmp->next;
		if (tmp->content)
		{
			free(tmp->content);
		}
		free(tmp);
		tmp = fr;
	}
	lst.cmds = NULL;
}
