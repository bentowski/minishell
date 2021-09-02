/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 18:38:04 by bbaudry           #+#    #+#             */
/*   Updated: 2021/09/02 22:43:37 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_childs(int in, int out, t_struct lst, char **env)
{
	pid_t	pid;
	char	*path;
	char	**cmd;

	pid = fork();
	if (pid == 0)
	{
		if (in != 0 && in != lst.cmds->file[0])
		{
			dup2(in, 0);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		select_cmd(lst, env, 2);
	}
	return (1);
}

static int	ft_father(int in, t_struct lst, char **env)
{
	char	*path;
	char	**cmd;

	if (in != 0)
		dup2(in, 0);
	dup2(lst.cmds->file[1], 1);
	select_cmd(lst, env, 2);
	return (1);
}

static int	cmd_count(t_list *cmds)
{
	t_list	*ptr;
	int		x;

	x = 0;
	ptr = cmds;
	while (ptr)
	{
		x++;
		ptr = ptr->next;
	}
	return (x);
}

static int	ft_pipex(t_struct lst, char **env, int opt)
{
	int	i;
	int	n;
	int	in;
	int	fd[2];

    in = 0;
	n = cmd_count(lst.cmds);
	i = 0;
	while (i < n - 1 && opt == 1)
	{
		pipe(fd);
        dup2(lst.cmds->file[0], 0);
		ft_childs(in, fd[1], lst, env);
		close(fd[1]);
		in = fd[0];
		i++;
		lst.cmds = lst.cmds->next;
	}
	ft_father(in, lst, env);
	return (1);
}

int	ft_pipe(t_struct lst, char **env)
{
	int			ret;
	int			pid;

    // lst.file[0] = 0;
    // lst.file[1] = 1;
	if (lst.cmds->next)
	{
		pid = fork();
		if (pid == 0)
			ft_pipex(lst, env, 1);
		else
			waitpid(pid, &ret, 0);
	}
	else
		ft_pipex(lst, env, 2);
	return (0);
}
