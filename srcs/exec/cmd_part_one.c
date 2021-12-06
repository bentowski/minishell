/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_part_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:34:31 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/06 16:33:35 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_error;

int	ft_env(t_struct lst, char **cmd_parts, char ***env)
{
	int	i;

	(void)cmd_parts;
	i = 0;
	while ((*env)[i])
		printf("%s\n", (*env)[i++]);
	if (lst.is_child)
		ft_exit(lst, cmd_parts, env);
	return (0);
}

int	ft_export(t_struct lst, char **cmd_parts, char ***env)
{
	int	i;
	int	flag;

	flag = 0;
	if (!cmd_parts[1])
		return (ft_env(lst, cmd_parts, env));
	i = 1;
	while (cmd_parts[i])
	{
		if (!ft_isalpha(cmd_parts[i][0]))
		{
			if (!flag)
				flag = error(NO_ALPH, &lst, cmd_parts[0], 0);
		}
		else
			ft_setenv(env, cmd_parts[i]);
		i++;
	}
	if (lst.is_child)
		ft_exit(lst, cmd_parts, env);
	return (0);
}

int	ft_unset(t_struct lst, char **cmd_parts, char ***env)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (cmd_parts[i])
	{
		if (!ft_isalpha(cmd_parts[i][0]))
		{
			if (!flag)
				flag = error(NO_ALPH, &lst, cmd_parts[0], 0);
		}
		else
			ft_unsetenv(env, cmd_parts[i]);
		i++;
	}
	if (lst.is_child)
		ft_exit(lst, cmd_parts, env);
	return (flag);
}

int	ft_exit_bi(t_struct lst, char **cmd_parts, char ***env)
{
	if (cmd_parts[1] && cmd_parts[2])
		return (error(TOO_MUCH, &lst, cmd_parts[0], 0));
	else if (cmd_parts[1])
	{
		if (non_num_found(cmd_parts[1]))
			g_error = error(NON_NUM_FOUND, &lst, cmd_parts[1], 0);
		else
			g_error = ft_atoi(cmd_parts[1]);
	}
	free(lst.err);
	del_cmd_list(&lst.cmd_line);
	ft_free(*env);
	rl_clear_history();
	if (!lst.is_child)
		printf("Bye bye 😎\n");
	exit(g_error);
}
