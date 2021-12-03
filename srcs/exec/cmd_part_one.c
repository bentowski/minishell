/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_part_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:34:31 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/03 23:02:27 by bbaudry          ###   ########.fr       */
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
		while (cmd_parts[x][0] == '-' && check_long_n(&cmd_parts[x][1]))
		{
			x++;
			n = -1;
		}
		while (cmd_parts[x])
		{
			ft_putstr_fd(cmd_parts[x++], 1);
			if (cmd_parts[x])
				write(1, " ", 1);
		}
	}
	if (n != -1)
		write(1, "\n", 1);
	if (lst.is_child)
	{
		ft_exit(lst, cmd_parts, env);
		exit (EXIT_SUCCESS);
	}
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
	if (cmd_parts[1])
		lst.exit_status = ft_atoi(cmd_parts[1]);
	ft_free(cmd_parts);
	ft_free(*env);
	rl_clear_history();
	if (!lst.is_child)
		printf("Bye bye 😎\n");
	exit(lst.exit_status);
}
