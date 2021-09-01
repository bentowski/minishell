/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:32:42 by bbaudry           #+#    #+#             */
/*   Updated: 2021/08/31 14:54:21 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_path_deux(char **possible, char **i, char *end_path)
{
	int		x;
	char	*tmp;
	char	*ret;
    struct stat sb;

	x = 0;
	while (possible[x])
	{
		tmp = ft_strjoin(possible[x], "/");
		ret = ft_strjoin(tmp, end_path);
		free(tmp);
		if (stat(ret, &sb) == 0)
			return (ret);
		free(ret);
		x++;
	}
	x = 0;
	while (i[x])
		free(i[x++]);
	free(i);
	x = 0;
	while (possible[x])
		free(possible[x++]);
	free(possible);
	return (NULL);
}

static char	*get_path(void *cmd, char **env)
{
	char	**possible;
	char	*path_line;
	char	**i;
	char	*ret;

	path_line = getenv("PATH");
	if (!path_line)
		return (NULL);
	path_line = ft_substr(path_line, 5, ft_strlen(path_line) - 5);
	possible = ft_split(path_line, ':');
	free(path_line);
	i = ft_split(cmd, ' ');
	ret = get_path_deux(possible, i, i[0]);
	return (ret);
}

static int ft_exec(char **cmd_parts, char **env, int opt)
{
	char *path;
	int pid;
	int ret;
	if (opt == 1)
	{
		pid = fork();
		if (pid == 0)
		{
			path = get_path(cmd_parts[0], env);
			if (path == NULL)
				return (-1);
			execve(path, cmd_parts, env);
		}
		else
			waitpid(pid, &ret, 0);
	}
	else
	{
		path = get_path(cmd_parts[0], env);
		if (path == NULL)
			return (-1);
		execve(path, cmd_parts, env);
	}
	ft_free(cmd_parts);
	return (1);
}

int select_cmd(t_struct lst, char **env, int opt)
{
	char *bltin[8] = { "echo", "cd", "pwd", "export", "unset", "env", "exit" };
	char **cmd_parts;
	int (*functions[7])(char **cmd_parts, char **env);
	int len;
	int x;

	cmd_parts = ft_split(lst.cmds->content, ' ');
	functions[0] = ft_echo;
	functions[1] = ft_cd;
	functions[2] = ft_pwd;
	functions[3] = ft_export;
	functions[4] = ft_unset;
	functions[5] = ft_env;
	functions[6] = ft_exit;
	x = -1;
	len = ft_strlen(cmd_parts[0]);
	while (bltin[++x])
		if (ft_strncmp(cmd_parts[0], bltin[x], len) == 0)
		{
			len = (*functions[x])(cmd_parts, env);
			ft_free(cmd_parts);
			return (len);
		}
	return (ft_exec(cmd_parts, env, opt));
}
