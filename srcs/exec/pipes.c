/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 18:38:04 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/06 08:23:48 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cmd_count(t_cmd_line *cmds)
{
	t_cmd_line	*ptr;
	int			x;

	x = 0;
	ptr = cmds;
	while (ptr)
	{
		x++;
		ptr = ptr->next;
	}
	return (x);
}

void	close_all(t_cmd_line *cmd)
{
	t_cmd_line	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->fd[0] != 0)
			close(tmp->fd[0]);
		if (tmp->fd[1] != 1)
			close(tmp->fd[1]);
		tmp = tmp->next;
	}
}

void	fd_free(int **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

int	**init_fd_tab(int len)
{
	int		i;
	int		**tab;

	tab = malloc(sizeof(int *) * (len + 1));
	i = 0;
	while (i < len)
		tab[i++] = malloc(sizeof(int) * 2);
	tab[i] = NULL;
	return (tab);
}

int	ft_run(t_struct *lst)
{
	int		ret;

	if (!lst->cmd_line->token)
		return (lst->exit_status);
	here_doc_checker(lst);
	ret = gestion_file(lst);
	if (ret)
		return (ret);
	lst->is_child = 0;
	if (cmd_count(lst->cmd_line) > 1 || do_fork(lst->cmd_line))
	{
		lst->is_child = 1;
		return (ft_pipes(cmd_count(lst->cmd_line), lst));
	}
	else
		return (no_pipe(lst));
	return (ret);
}
