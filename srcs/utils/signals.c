/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:43:15 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/06 16:32:34 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_error;

void	handle_sigint(int signal)
//ctrl c
{
	(void)signal;
	write(1, "\n", 1);
	g_error = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigint_ii(int signal)
//ctrl c
{
	(void)signal;
	g_error = 130;
	write(1, "\n", 1);
}

void	handle_sigquit(int signal)
{
	(void)signal;
	write(2, "Quit (core dumped)\n", ft_strlen("Quit (core dumped)\n"));
	write(1, "  ", 2);
	write(1, "\b\b", 2);
}
