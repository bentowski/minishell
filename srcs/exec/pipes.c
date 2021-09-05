/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 18:38:04 by bbaudry           #+#    #+#             */
/*   Updated: 2021/09/05 09:59:43 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int gestion_file(t_struct lst, char **cmd_parts)
{
	int x;
	int ret;

	x = 0;
	ret = 0;
	while (cmd_parts[x])
	{
		if (ft_strncmp(cmd_parts[x], "<", 2) == 0)
		{
			lst.cmds->file[0] = open(cmd_parts[x + 1], O_RDONLY);
			if (lst.cmds->file[0] < 0)
				return (0);
			free(cmd_parts[x]);
			free(cmd_parts[x + 1]);
			cmd_parts[x] = NULL;
			if (ret == x)
				ret = x + 2;
			x++;
		}
		else if (ft_strncmp(cmd_parts[x], ">", 2) == 0)
		{
			lst.cmds->file[1] = open(cmd_parts[x + 1], O_WRONLY | O_TRUNC | O_CREAT, 402);
			if (lst.cmds->file[1] < 0)
				return (0);
			free(cmd_parts[x]);
			free(cmd_parts[x + 1]);
			cmd_parts[x] = NULL;
			if (ret == x)
				ret = x + 2;
			x++;
		}
		x++;
	}
	if (!cmd_parts[ret])
		return (0);
	return (ret);
}

static int	ft_childs(int in, int out, t_struct lst, char **cmd_parts)
{
	pid_t	pid;
	char	*path;
	char	**cmd;
	int x;

	x = 0;
	pid = fork();
	if (pid == 0)
	{
		if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		select_cmd(lst, cmd_parts);
	}
	return (1);
}


static int	ft_pipex(t_struct lst)
{
	int	i;
	int	n;
	int	in;
	int x;
	int	fd[2];
	char **cmd_parts;

	cmd_parts = ft_split(lst.cmds->content, ' ');
	x = gestion_file(lst, cmd_parts);
	in = lst.cmds->file[0];
	n = cmd_count(lst.cmds);
	i = 0;
	while (i < n - 1)
	{
		pipe(fd);
		if (lst.cmds->file[1] != 1)
			fd[1] = lst.cmds->file[1];
		ft_childs(in, fd[1], lst, &cmd_parts[x]);
		in = fd[0];
		close(fd[1]);
		i++;
		lst.cmds = lst.cmds->next;
		ft_free(cmd_parts);
		x = 0;
		cmd_parts = ft_split(lst.cmds->content, ' ');
		x = gestion_file(lst, cmd_parts);
	}
	if (in != 0)
		dup2(in, 0);
	printf("%d\n", lst.cmds->file[1]);
	dup2(lst.cmds->file[1], 1);
	return (select_cmd(lst, &cmd_parts[x]));
}



int	ft_pipe(t_struct lst)
{
	int		ret;
	int		pid;

	pid = fork();
	if (pid == 0)
	{
		return (ft_pipex(lst));
	}
	else
	{
		waitpid(pid, &ret, 0);
	}
	return (0);
}
