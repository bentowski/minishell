/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 06:17:06 by vgallois          #+#    #+#             */
/*   Updated: 2021/12/06 06:17:09 by vgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	_openpipe(t_cmd_line *cmd, int len, int i)
{
	t_cmd_line	*tmp;
	int			**fd;

	fd = init_fd_tab(len);
	tmp = cmd;
	while (tmp)
	{
		pipe(fd[i]);
		if (!i)
			tmp->fd[0] = 0;
		else
			tmp->fd[0] = fd[i - 1][0];
		if (!tmp ->next)
		{
			close(fd[i][0]);
			close(fd[i][1]);
			tmp->fd[1] = 1;
		}
		else
			tmp->fd[1] = fd[i][1];
		tmp = tmp->next;
		i++;
	}
	fd_free(fd);
}

static void	_putfile(t_cmd_line *cmd)
{
	t_cmd_line	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->file[0] != 0)
		{
			if (tmp->fd[0] != 0)
				close(tmp->fd[0]);
			tmp->fd[0] = tmp->file[0];
		}
		if (tmp->file[1] != 1)
		{
			if (tmp->fd[1] != 1)
				close(tmp->fd[1]);
			tmp->fd[1] = tmp->file[1];
		}
		tmp = tmp->next;
	}
}

static void	_execcmd(t_cmd_line *cmd, t_struct *lst, int i, pid_t *pid)
{
	pid[i] = fork();
	if (!pid[i])
	{
		dup2(cmd->fd[0], 0);
		dup2(cmd->fd[1], 1);
		close_all(lst->cmd_line);
		free(pid);
		lst->exit_status = select_cmd(*lst, cmd);
		ft_exit(*lst, NULL, lst->env);
	}
	if (cmd->fd[0] != 0)
		close(cmd->fd[0]);
	if (cmd->fd[1] != 1)
		close(cmd->fd[1]);
}

int	ft_pipes(int n, t_struct *lst)
{
	int			i;
	t_cmd_line	*tmp;
	pid_t		*pid;
	int			ret;

	i = -1;
	tmp = lst->cmd_line;
	_openpipe(tmp, n, 0);
	_putfile(tmp);
	pid = malloc(sizeof(pid_t) * n);
	while (++i < n)
	{
		_execcmd(tmp, lst, i, pid);
		tmp = tmp->next;
	}
	i = 0;
	while (i < n)
	{
		waitpid(pid[i++], &ret, 0);
		if (WIFEXITED(ret))
			ret = WEXITSTATUS(ret);
	}
	free(pid);
	return (ret);
}

int	no_pipe(t_struct *lst)
{
	int	ret;

	lst->startin = dup(0);
	lst->startout = dup(1);
	dup2(lst->cmd_line->file[0], 0);
	dup2(lst->cmd_line->file[1], 1);
	ret = select_cmd(*lst, lst->cmd_line);
	dup2(lst->startin, 0);
	dup2(lst->startout, 1);
	return (ret);
}
