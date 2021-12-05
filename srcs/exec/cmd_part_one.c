/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_part_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:34:31 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/05 20:25:58 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


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

	i = 1;
	if (!ft_isalpha(cmd_parts[i][0]))
		return (error(NO_ALPH, &lst, cmd_parts[0], 0));
	while (cmd_parts[i])
	{
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

	i = 1;
	while (cmd_parts[i])
	{
		ft_unsetenv(env, cmd_parts[i]);
		i++;
	}
	if (lst.is_child)
		ft_exit(lst, cmd_parts, env);
	return (0);
}

int	ft_exit_bi(t_struct lst, char **cmd_parts, char ***env)//gerer les erreurs
{
	if (cmd_parts[1] && cmd_parts[2])
		return (error(TOO_MUCH, &lst, cmd_parts[0], 0));
	else if (cmd_parts[1])
	{
		if (non_num_found(cmd_parts[1]))
			lst.exit_status = error(NON_NUM_FOUND, &lst, cmd_parts[1], 0);
		else
			lst.exit_status = ft_atoi(cmd_parts[1]);
	}
	del_cmd_list(&lst.cmd_line);
	ft_free(*env);
	rl_clear_history();
	if (!lst.is_child)
		printf("Bye bye 😎\n");
	exit(lst.exit_status);
}
