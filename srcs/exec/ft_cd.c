/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:07:37 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/05 03:04:23 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cd_base(t_struct lst)
{
	char	*new;
	int		ret;

	new = ft_get_env("HOME", *(lst.env));
	if (new)
		ret = chdir(new);
	else
		ret = chdir("/");
	free(new);
	return (ret);
}

static int	cd_relative(char **cmd_parts, char *buf, size_t len)
{
	char	*target;
	int		x;
	int		y;

	target = malloc(len + ft_strlen(cmd_parts[1]) + 1);
	if (!target)
		return (error(MEM_ERR, NULL, NULL, 0));
	x = 0;
	while (buf[x])
	{
		target[x] = buf[x];
		x++;
	}
	target[x] = '/';
	y = 0;
	while (cmd_parts[1][y])
	{
		target[x + y + 1] = cmd_parts[1][y];
		y++;
	}
	target[x + y + 1] = '\0';
	x = chdir(target);
	free(target);
	return (x);
}

static int	cd_part2(t_struct lst, char **cmd_parts, char *buf, size_t len)
{
	if (cmd_parts[1] == NULL || !ft_strncmp(cmd_parts[1], "~", 2))
	{
		if (cd_base(lst))
			return (error(MEM_ERR, &lst, NULL, 0));
	}
	else if (cmd_parts[2] != NULL)
		return (error(MEM_ERR, &lst, NULL, 0));
	else if ((chdir(cmd_parts[1]) == -1)
		&& (cd_relative(cmd_parts, buf, len) == -1))
	{
		free(buf);
		return (error(BAD_FILE, &lst, cmd_parts[1], 0));
	}
	free(buf);
	if (lst.is_child)
		ft_exit(lst, cmd_parts, lst.env);
	return (0);
}

static void	_set_old_env(char ***env, char *s)
{
	char	*tmp;

	tmp = ft_strdup("OLDPWD=");
	s = clean_join(tmp, s);
	ft_setenv(env, s);
	free(s);
}

int	ft_cd(t_struct lst, char **cmd_parts, char ***env)
{
	char	*buf;
	size_t	len;
	int		ret;
	char	*oldpwd;

	oldpwd = ft_pwd_in();
	len = 1;
	buf = malloc(len * sizeof(char));
	if (!buf)
		return (error(MEM_ERR, &lst, NULL, 0));
	while (getcwd(buf, len) == NULL)
	{
		free(buf);
		len++;
		buf = malloc(len * sizeof(char));
		if (!buf)
			return (error(MEM_ERR, &lst, NULL, 0));
	}
	ret = cd_part2(lst, cmd_parts, buf, len);
	if (!ret)
		_set_old_env(env, oldpwd);
	else
		free(oldpwd);
	return (ret);
}
