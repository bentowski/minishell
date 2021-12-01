/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_part_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:34:31 by bbaudry           #+#    #+#             */
/*   Updated: 2021/11/30 19:45:58 by vgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_struct lst, char **cmd_parts, char ***env)
{
	int		x;
	int		n;

	(void)env;
	n = 1;
	if ((cmd_parts[1]))
	{
		x = 1;
		n = ft_strncmp(cmd_parts[1], "-n", 2);
		if (n == 0)
			x = 2;
		while (cmd_parts[x])
		{
			ft_putstr_fd(cmd_parts[x++], 1);
			if (cmd_parts[x])
				write(1, " ", 1);
		}
	}
	if (n != 0)
		write(1, "\n", 1);
	if (lst.is_child)
		exit (EXIT_SUCCESS);
	return (0);
}

int	cd_base(t_struct lst)
{
	char	*new;
	int		ret;

	new = ft_get_env("HOME", *(lst.env));
	if (new)
		ret = chdir(new);
	else
		ret = chdir("/");
	return (ret);
}

int	cd_relative(char **cmd_parts, char *buf, size_t len)
{
	char	*target;
	int		x;
	int		y;

	target = malloc(len + ft_strlen(cmd_parts[1]));
	if (!target)
		return (error(MEM_ERR, NULL, NULL, 0));
	x = 0;
	while (buf[x])
	{
		target[x] = buf[x];
		x++;
	}
	y = 0;
	while (cmd_parts[1][y])
	{
		target[x + y + 1] = cmd_parts[1][y];
		y++;
	}
	target[x + y] = '\0';
	if (chdir(target) == -1)
		return (error(MEM_ERR, NULL, NULL, 0));
	return (0);
	exit(EXIT_SUCCESS);
}

static int	cd_part2(t_struct lst, char **cmd_parts, char *buf, size_t len)
{
	if (cmd_parts[1] == NULL)
	{
		if (cd_base(lst))
			return (error(MEM_ERR, NULL, NULL, 0));
	}
	else if (cmd_parts[2] != NULL)
		return (error(MEM_ERR, NULL, NULL, 0));
	else if ((chdir(cmd_parts[1]) == -1)
		&& (cd_relative(cmd_parts, buf, len) == -1))
	{
		printf("%s : no such file or directory\n", cmd_parts[1]);
		free(buf);
		return (error(MEM_ERR, NULL, NULL, 0));
	}
	free(buf);
	if (lst.is_child)
		exit(0);
	return (0);
}

int	ft_cd(t_struct lst, char **cmd_parts, char ***env)
{
	char	*buf;
	size_t	len;

	(void)env;
	len = 1;
	buf = malloc(len * sizeof(char));
	if (!buf)
		return (error(MEM_ERR, NULL, NULL, 0));
	while (getcwd(buf, len) == NULL)
	{
		free(buf);
		len++;
		buf = malloc(len * sizeof(char));
		if (!buf)
			return (error(MEM_ERR, NULL, NULL, 0));
	}
	return (cd_part2(lst, cmd_parts, buf, len));
}

char	*ft_pwd_in(void)
{
	char	*buf;
	size_t	len;

	len = 0;
	buf = malloc(len * sizeof(char));
	if (!buf)
		return (NULL);
	while (getcwd(buf, len) == NULL)
	{
		free(buf);
		len++;
		buf = malloc(len * sizeof(char));
		if (!buf)
			return (NULL);
	}
	return (buf);
}

int	ft_pwd(t_struct lst, char **cmd_parts, char ***env)
{
	char	*buf;
	size_t	len;

	(void)env;
	(void)cmd_parts;
	len = 0;
	buf = malloc(len * sizeof(char));
	if (!buf)
		return (error(MEM_ERR, NULL, NULL, 0));
	while (getcwd(buf, len) == NULL)
	{
		free(buf);
		len++;
		buf = malloc(len * sizeof(char));
		if (!buf)
			return (error(MEM_ERR, NULL, NULL, 0));
	}
	ft_putstr_fd(buf, 1);
	write(1, "\n", 1);
	free(buf);
	if (lst.is_child)
		exit (EXIT_SUCCESS);
	return (0);
}

int	ft_env(t_struct lst, char **cmd_parts, char ***env)
{
	int	i;

	(void)cmd_parts;
	i = 0;
	while ((*env)[i])
		printf("%s\n", (*env)[i++]);
	if (lst.is_child)
		exit (EXIT_SUCCESS);
	return (0);
}

int	ft_export(t_struct lst, char **cmd_parts, char ***env)
{
	int	i;

	i = 1;
	while (cmd_parts[i])
	{
		ft_setenv(env, cmd_parts[i]);
		i++;
	}
	ft_env(lst, cmd_parts, env);
	if (lst.is_child)
		exit (EXIT_SUCCESS);
	return (0);
}

int	ft_unset(t_struct lst, char **cmd_parts, char ***env)
{
	int	i;

	i = 1;
	while (cmd_parts[i])
	{
		ft_unsetenv(env, cmd_parts[i]);
		i++;
	}
	if (lst.is_child)
		exit (EXIT_SUCCESS);
	return (0);
}

int	ft_exit(t_struct lst, char **cmd_parts, char ***env)
{
	(void)lst;
	ft_free(cmd_parts);
	ft_free(*env);
	rl_clear_history();
	printf("Bye bye\n");
	exit(EXIT_SUCCESS);
}
