/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:38:31 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/06 15:39:22 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_error;

int	real_start(t_struct *lst, int end)
{
	int	ret;

	if (lst->cmd_line)
	{
		ret = ft_run(lst);
		if (ret == -1)
			end = 1;
		else
			g_error = ret;
		if (lst->here_doc_content)
		{
			free(lst->here_doc_content);
			lst->here_doc_content = NULL;
		}
		if (lst->cmd_line)
			del_cmd_list(&lst->cmd_line);
	}
	return (end);
}

int	start(t_struct lst)
{
	int	end;

	end = 0;
	while (end == 0)
	{
		lst.is_child = 0;
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, handle_sigquit);
		lst.here_doc_flag = 0;
		ft_parsing(&lst);
		end = real_start(&lst, end);
	}
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_struct	lst;
	int			ret;

	lst.err = malloc(sizeof(char *) * 13);
	if (argc != 1)
		return (error(BAD_ARG, NULL, argv[1], 0));
	printf("Welcome to minishell\n");
	env = first_env(env);
	lst.err = errors(lst.err);
	lst.env = &env;
	lst.here_doc_flag = 0;
	lst.here_doc_content = 0;
	lst.limiter = NULL;
	g_error = 0;
	lst.cmd_line = 0;
	lst.is_child = 0;
	ret = start(lst);
	ft_free(env);
	rl_clear_history();
	return (ret);
}
