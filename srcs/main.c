/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:38:31 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/04 01:19:54 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	start(t_struct lst)
{
	int	end;
	int	ret;

	end = 0;
	while (end == 0)
	{
		lst = ft_parsing(lst);
		lst.here_doc_flag = 0;
		if (lst.cmds)
		{
			ret = ft_run(&lst);
			if (ret == -1)
				end = 1;
			else
				lst.exit_status = ret;
			if (lst.here_doc_content)
			{
				free(lst.here_doc_content);
				lst.here_doc_content = NULL;
			}
		}
	}
	return (ret);
}

int	main(int argc, char **argv, char **env)
{
	t_struct	lst;
	int			ret;

	(void)argv;
	(void)argc;
	// if (argc > 1)
	// 	return (error(BAD_ARG, NULL, NULL, 1));
	printf("Welcome to minishell\n");
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);
	env = first_env(env);
	lst.env = &env;
	lst.here_doc_flag = 0;
	lst.here_doc_content = 0;
	lst.limiter = NULL;
	lst.exit_status = 0;
	ret = start(lst);
	ft_free(env);
	rl_clear_history();
	return (ret);
}
