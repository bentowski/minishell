/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 14:30:16 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/06 14:50:46 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **errors(char **error)
{
	printf("%d\n", UKN_ERR);
	error[UKN_ERR] = "Unknown error.";
	error[MEM_ERR] = "Memory allocation failed while parsing shapes.";
	error[BAD_FILE] = "no such file or directory.";
	error[QUOTE_ERR] = "quotes or double quotes not closed.";
	error[NO_VAR] = "no variables found";
	error[BAD_ARG] = "no arguments is supported.";
	error[TOO_MUCH] = "too many arguments.";
	error[LON_PIPE] = "pipe without command.";
	error[NON_NUM_FOUND] = "numeric argument required.";
	error[NO_ALPH] = "alphabetic argument required.";
	error[NO_PERM] = "permission denied or cannot be executed.";
	error[UN_TOKEN] = "syntax error near unexpected token";
	error[12] = NULL;
	return (error);
}

static	char	*get_error_msg(t_struct *lst, t_err raised)
{
	if (raised != ERRNO_TO_STR)
		return (lst->err[raised]);
	return ((char *)strerror(errno));
}

int	error(t_err raised, t_struct *lst, char *line, int critical)
{
	char	*msg;

	msg = get_error_msg(lst, raised);
	lst->exit_status = raised;
	printf("minishell: %s: %s\n", line, msg);
	if (critical)
	{
		lst_free(*lst);
		rl_clear_history();
		exit(raised);
	}
	else
		return (raised);
}
