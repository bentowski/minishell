/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:43:15 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/06 15:40:24 by bbaudry          ###   ########.fr       */
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
	write(2, "Quit (core dumped)\n", ft_strlen("Quit (core dumped)\n"));
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_sigquit(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  ", 2);
	write(1, "\b\b", 2);
	rl_redisplay();
}

void	handle_sigint_ii(int signal)
//ctrl c
{
	(void)signal;
	g_error = 130;
	write(1, "\n", 1);
}

void	handle_sigquit_ii(int signal)
{
	(void)signal;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  ", 2);
	write(1, "\b\b", 2);
	rl_redisplay();
}
