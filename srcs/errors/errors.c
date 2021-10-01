/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/29 14:30:16 by bbaudry           #+#    #+#             */
/*   Updated: 2021/09/28 16:15:38 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

static t_error	g_errors[] =
{
	{UKN_ERR, "Unknown error." },
	{MEM_ERR, "Memory allocation failed while parsing shapes." },
	{QUOTE_ERR, "quotes or double quotes not closed." },
	{BAD_FILE, "no such file or directory." }
	// {NB_ARG, "Invalid call: Incorrect number of arguments." },
	// {FILE_FRMT, "Invalid file: Use the '.ber' extension." },
	// {READ_ERR, "Invalid file: cannot read input file." },
	// {CLOSEMAP_ERR, "Invalid map: unclosed." },
	// {MAP_CFG, "Invalid map: no regular map" },
	// {BADCHAR_ERR, "Invalid map: unexpected character detected" },
	// {NOE_ERR, "Invalid map: no or multiple exit(s) detected" },
	// {NOP_ERR, "Invalid map: no or multiple player(s) detected" },
	// {NOC_ERR, "Invalid map: no collectors detected" }
};

static	char	*get_error_msg(t_err raised)
{
	if (raised != ERRNO_TO_STR)
		return (g_errors[raised].msg);
	return ((char *)strerror(errno));
}

int	error(t_err raised, t_struct lst, char *line, int critical)
{
	char	*msg;

	// if (line)
	// 	free(line);
	// if (env)
	// 	ft_free(env);
	msg = get_error_msg(raised);
	printf("%s: %s\n", line, msg);
	if (critical)
	{
		rl_clear_history();
		exit(EXIT_FAILURE);
	}
	else
		return (-1);
}
