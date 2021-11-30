/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 18:38:04 by bbaudry           #+#    #+#             */
/*   Updated: 2021/11/30 15:46:51 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../errors/errors.h"

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



static int	set_limiter(t_struct *lst, char *s)
{
	if (lst->limiter)
	{
		printf("set_limiter freed %s\n", lst->limiter);
		free(lst->limiter);
	}
	lst->limiter = ft_strdup(s);
	if (!lst->limiter)
		return (1);
	return (0);
}

static int gestion_file(t_struct *lst, char **cmd_parts)
{
	int x;
	int ret;

	x = 0;
	ret = 0;
	while (cmd_parts[x])
	{
		if (cmd_parts[x][0] == '<')
		{
			if (cmd_parts[x][1] == '<')
			{
				lst->here_doc_flag = 1;
				if (!cmd_parts[x][2])
				{
					if (set_limiter(lst, cmd_parts[x + 1]))
						return (error(MEM_ERR, *lst, cmd_parts[x + 1], 1));
					ret = test(cmd_parts, x++, ret);
				}
				else
				{
					if (set_limiter(lst, cmd_parts[x] + 2))
						return (error(MEM_ERR, *lst, cmd_parts[x] + 2, 1));
					ret = test(cmd_parts, x, ret);
				}
			}
			else
			{
				lst->here_doc_flag = 0;
			// if (cmds_parts[x][1] == '<')
			// {
			// 	if (cmd_parts[x][2] == '\0')
			// 	{
			// 		lst.cmds->file[0] = open(cmd_parts[x + 1], O_RDONLY);
			// 		if (lst.cmds->file[0] < 0)
			// 			return (-1);
			// 		ret = test(cmd_parts, x++, ret);
			// 	}
			// 	else
			// 	{
			// 		lst.cmds->file[0] = open(&cmd_parts[x][2], O_RDONLY);
			// 		if (lst.cmds->file[0] < 0)
			// 			return (-1);
			// 		ret = test(cmd_parts, x, ret);
			// 	}
			// }
				if (cmd_parts[x][1] == '\0')
				{
					lst->cmds->file[0] = open(cmd_parts[x + 1], O_RDONLY);
					if (lst->cmds->file[0] < 0)
						return (error(BAD_FILE, *lst, cmd_parts[x + 1], 0));
					ret = test(cmd_parts, x++, ret);
				}
				else
				{
					lst->cmds->file[0] = open(&cmd_parts[x][1], O_RDONLY);
					if (lst->cmds->file[0] < 0)
						return (error(BAD_FILE, *lst, &cmd_parts[x][1], 0));
					ret = test(cmd_parts, x, ret);
				}
			}
		}
		else if (cmd_parts[x][0] == '>')
		{
			if (cmd_parts[x][1] == '>')
			{
				if (cmd_parts[x][2] == '\0')
				{
					lst->cmds->file[1] = open(cmd_parts[x + 1], O_APPEND | O_WRONLY | O_CREAT, 402);
					if (lst->cmds->file[1] < 0)
						return (error(BAD_FILE, *lst, cmd_parts[x + 1], 0));
					ret = test(cmd_parts, x++, ret);
				}
				else
				{
					lst->cmds->file[1] = open(&cmd_parts[x][2], O_APPEND | O_WRONLY | O_CREAT, 402);
					if (lst->cmds->file[1] < 0)
						return (error(BAD_FILE, *lst, &cmd_parts[x][1], 0));
					ret = test(cmd_parts, x, ret);
				}
			}
			else if (cmd_parts[x][1] == '\0')
			{
				lst->cmds->file[1] = open(cmd_parts[x + 1], O_WRONLY | O_TRUNC | O_CREAT, 402);
				if (lst->cmds->file[1] < 0)
					return (error(BAD_FILE, *lst, cmd_parts[x + 1], 0));
				ret = test(cmd_parts, x++, ret);
			}
			else
			{
				lst->cmds->file[1] = open(&cmd_parts[x][1], O_WRONLY | O_TRUNC | O_CREAT, 402);
				if (lst->cmds->file[1] < 0)
					return (error(BAD_FILE, *lst, &cmd_parts[x][1], 0));
				ret = test(cmd_parts, x, ret);
			}
		}

		x++;
	}
	if (lst->here_doc_flag)
		lst->here_doc_content = here_doc_read(lst);
	if (!cmd_parts[ret])
		return (-1);
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
	int		x;

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
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &x, 0);
		return (1);
	}
}

static int ft_pipes(int n, int x, t_struct lst, char **cmd_parts)
{
	int in;
	int i;
	int	fd[2];
	t_list *ptr;
	int ret;

	ptr = lst.cmds;
	in = lst.cmds->file[0];
	i = 0;
	while (i < n - 1)
	{
		pipe(fd);
		ft_childs(in, fd[1], lst, &cmd_parts[x]);
		in = fd[0];
		close(fd[1]);
		i++;
		x = 0;
		lst.cmds = lst.cmds->next;
		// lst.cmds->content = third_lecture(lst.cmds->content);
		ft_free(cmd_parts);
		cmd_parts = ft_split(lst.cmds->content, ' ');
		x = gestion_file(&lst, cmd_parts);
		if (x == -1)
			return (0);
	}
	dup2(1, 1);
	dup2(in, 0);
	dup2(lst.cmds->file[1], 1);
	ret = select_cmd(lst, &cmd_parts[x]);
	return (ret);
}

int	ft_run(t_struct *lst)
{
	int		ret;
	int		pid;
	int		x;
	char	**cmd_parts;

	// lst->cmds->content = third_lecture(lst->cmds->content);
	cmd_parts = ft_split(lst->cmds->content, ' ');
	x = gestion_file(lst, cmd_parts);
	if (x == -1)
		return (0);
	if (cmd_count(lst->cmds) > 1 || !do_fork(&cmd_parts[x]))
	{
		pid = fork();
		if (pid == 0)
			return (ft_pipes(cmd_count(lst->cmds), x, *lst, cmd_parts));
		else
		{
			ft_free(cmd_parts);
			waitpid(pid, &ret, 0);
		}
	}
	else
		return (ft_pipes(cmd_count(lst->cmds), x, *lst, cmd_parts));
	return (0);
}
