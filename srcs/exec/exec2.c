/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 16:33:05 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/06 16:33:08 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	found_arg(t_cmd_line *cmd)
{
	t_token	*token;

	token = cmd->token;
	while (token)
	{
		if (token->type == ARG)
			return (1);
		token = token->next;
	}
	return (0);
}
