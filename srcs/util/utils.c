/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 10:25:52 by bbaudry           #+#    #+#             */
/*   Updated: 2021/11/24 14:45:48 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int do_fork(char **cmd_parts)
{
	char	*bltin[8] = { "echo", "cd", "pwd", "export", "unset", "env", "exit" };
	int		x;
	int		len;

    x = 0;
	len = ft_strlen(cmd_parts[0]);
	while (bltin[++x])
		if (ft_strncmp(cmd_parts[0], bltin[x], len) == 0)
            return (1);
	return (0);
}
