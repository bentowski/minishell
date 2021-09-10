/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 18:38:04 by bbaudry           #+#    #+#             */
/*   Updated: 2021/09/10 22:41:02 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int test(char **cmd_parts, int x, int ret)
{
	if (cmd_parts[x][1] == '\0')
	{
		free(cmd_parts[x]);
		free(cmd_parts[x + 1]);
		cmd_parts[x] = NULL;
		if (ret == x)
			ret = x + 2;
	}
	else
	{
		free(cmd_parts[x]);
		cmd_parts[x] = NULL;
		if (ret == x)
			ret = x + 1;
	}
	return (ret);
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
		if (line[x] == 39)
		{
			while (line[++x] && line[x] != 39)
				count++;
			if (!line[x])
				return (NULL);
			count--;
		}
		else if (line[x] == 34)
		{
			while (line[++x] && line[x] != 34)
				count++;
			if (!line[x])
				return (NULL);
			count--;
		}
		count++;
		x++;
	}
	new = malloc(sizeof(char) * (count + 1));
	if (!new)
		return (NULL);
	x = -1;
	y = 0;
	while (line[++x])
		if (line[x] == 34)
			while (line[++x] && line[x] != 34)
				new[y++] = line[x];
		else if (line[x] == 39)
			while (line[++x] && line[x] != 39)
				new[y++] = line[x];
		else
			new[y++] = line[x];
	new[y] = '\0';
	free(line);
	return (new);
}

static int gestion_file(t_struct lst, char **cmd_parts)
{
	int x;
	int ret;

	x = 0;
	ret = 0;
	while (cmd_parts[x])
	{
		if (cmd_parts[x][0] == '<')
		{
			if (cmd_parts[x][1] == '\0')
			{
				lst.cmds->file[0] = open(cmd_parts[x + 1], O_RDONLY);
				if (lst.cmds->file[0] < 0)
					return (-1);
				ret = test(cmd_parts, x++, ret);
			}
			else
			{
				lst.cmds->file[0] = open(&cmd_parts[x][1], O_RDONLY);
				if (lst.cmds->file[0] < 0)
					return (-1);
				ret = test(cmd_parts, x, ret);
			}
		}
		else if (cmd_parts[x][0] == '>')
		{
			if (cmd_parts[x][1] == '\0')
			{
				lst.cmds->file[1] = open(cmd_parts[x + 1], O_WRONLY | O_TRUNC | O_CREAT, 402);
				if (lst.cmds->file[1] < 0)
					return (-1);
				ret = test(cmd_parts, x++, ret);
			}
			else
			{
				lst.cmds->file[1] = open(&cmd_parts[x][1], O_WRONLY | O_TRUNC | O_CREAT, 402);
				if (lst.cmds->file[1] < 0)
					return (-1);
				ret = test(cmd_parts, x, ret);
			}
		}
		x++;
	}
	if (!cmd_parts[ret])
		return (0);
	return (ret);
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

static int	ft_childs(int in, int out, t_struct lst, char **cmd_parts)
{
	pid_t	pid;
	char	*path;
	char	**cmd;
	int x;

	x = 0;
	if (lst.cmds->file[1] != 1)
		out = lst.cmds->file[1];
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

static int ft_pipes(int n, int x, t_struct lst, char **cmd_parts)
{
	int in;
	int i;
	int	fd[2];
	t_list *ptr;

	in = lst.cmds->file[0];
	i = 0;
	lst.cmds->content = third_lecture(lst.cmds->content);
	while (i < n - 1)
	{
		pipe(fd);
		ft_childs(in, fd[1], lst, &cmd_parts[x]);
		in = fd[0];
		close(fd[1]);
		i++;
		ptr = lst.cmds;
		lst.cmds = lst.cmds->next;
		free(ptr->content);
		free(ptr);
		lst.cmds->content = third_lecture(lst.cmds->content);
		ft_free(cmd_parts);
		x = 0;
		lst.cmds->content = third_lecture(lst.cmds->content);
		cmd_parts = ft_split(lst.cmds->content, ' ');
		x = gestion_file(lst, cmd_parts);
		if (x == -1)
			return (0);
	}
	dup2(in, 0);
	dup2(lst.cmds->file[1], 1);
	return (select_cmd(lst, &cmd_parts[x]));
}

int	ft_run(t_struct lst)
{
	int		ret;
	int		pid;
	int x;
	char **cmd_parts;

	pid = fork();
	if (pid == 0)
	{
		lst.cmds->content = third_lecture(lst.cmds->content);
		cmd_parts = ft_split(lst.cmds->content, ' ');
		x = gestion_file(lst, cmd_parts);
		if (x == -1)
			return (0);
		return (ft_pipes(cmd_count(lst.cmds), x, lst, cmd_parts));
	}
	else
		waitpid(pid, &ret, 0);
	return (0);
}
