/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 14:30:16 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/05 01:14:57 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_error	g_errors[] = {
{UKN_ERR, "Unknown error." },
{MEM_ERR, "Memory allocation failed while parsing shapes." },
{QUOTE_ERR, "quotes or double quotes not closed." },
{NO_VAR, "no variables found"},
{BAD_ARG, "no arguments is supported." },
{BAD_FILE, "no such file or directory." },
{TOO_MUCH, "too many arguments."},
{LON_PIPE, "pipe whithout next command."},
{NON_NUM_FOUND, "numeric argument required"}
};

static	char	*get_error_msg(t_err raised)
{
	if (raised != ERRNO_TO_STR)
		return (g_errors[raised].msg);
	return ((char *)strerror(errno));
}

int	error(t_err raised, t_struct *lst, char *line, int critical)
{
	char	*msg;

	msg = get_error_msg(raised);
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
