/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:32:42 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/06 08:13:30 by vgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*_try_relative(char *cmd)
{
	char	*dir;
	char	*tmp;

	dir = ft_pwd_in();
	tmp = ft_strjoin(dir, "/");
	free(dir);
	dir = ft_strjoin(tmp, cmd);
	free(tmp);
	if (access(dir, X_OK))
	{
		free(dir);
		return (NULL);
	}
	return (dir);
}

static char	*_try_absolute(char *cmd)
{
	char	*res;

	if (access(cmd, X_OK))
		return (NULL);
	res = ft_strdup(cmd);
	return (res);
}

static int	ft_exec(t_struct lst, char **cmd_parts, char ***env)
{
	char	*path;
	int		ret;
	int		x;

	ret = -1;
	x = 0;
	path = get_path(cmd_parts[0], env);
	if (!path)
		path = _try_relative(cmd_parts[0]);
	if (!path)
		path = _try_absolute(cmd_parts[0]);
	if (path)
	{
		if (lst.here_doc_flag)
			ret = here_doc_exec(path, lst, cmd_parts, env);
		else
			ret = execve(path, cmd_parts, *env);
		free(path);
		error(NO_PERM, &lst, cmd_parts[0], 0);
	}
	else
		error(BAD_FILE, &lst, cmd_parts[0], 0);
	return (ret);
}

static void	_mapping(char **bltin,
	int (*functions[7])(t_struct, char **, char ***))
{
	bltin[0] = "echo";
	bltin[1] = "cd";
	bltin[2] = "pwd";
	bltin[3] = "export";
	bltin[4] = "unset";
	bltin[5] = "env";
	bltin[6] = "exit";
	bltin[7] = NULL;
	functions[0] = ft_echo;
	functions[1] = ft_cd;
	functions[2] = ft_pwd;
	functions[3] = ft_export;
	functions[4] = ft_unset;
	functions[5] = ft_env;
	functions[6] = ft_exit_bi;
}

int	select_cmd(t_struct lst, t_cmd_line *cmd)
{
	char	*bltin[8];
	int		(*functions[7])(t_struct lst, char **cmd_parts, char ***env);
	int		x;
	int		len;

	_mapping(bltin, functions);
	cmd->arg = token_join(cmd->token);
	x = -1;
	lst.here_doc_flag = cmd->here_doc_flag;
	lst.here_doc_content = cmd->here_doc_content;
	while (bltin[++x])
	{
		if (ft_strncmp(cmd->arg[0], bltin[x], ft_strlen(bltin[x]) + 1) == 0)
		{
			len = (*functions[x])(lst, cmd->arg, lst.env);
			return (len);
		}
	}
	return (ft_exec(lst, cmd->arg, lst.env));
}
