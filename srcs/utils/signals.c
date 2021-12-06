/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:43:15 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/06 01:23:17 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_sigint(int signal)
{
	(void)signal;
	write(1, "\n", 1);
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
{
	(void)signal;
	write(1, "\n", 1);
	// rl_on_new_line();
	// rl_replace_line("", 0);
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
