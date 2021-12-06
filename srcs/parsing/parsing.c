/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 12:49:29 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/06 11:21:20 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_c(char c, char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = -1;
	while (s[++i])
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '"')
				i++;
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\'')
				i++;
		}
		if (s[i] == c)
			return (i);
	}
	return (i);
}

static char	*_dup_to_pipe(char *line, int len)
{
	char	*res;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, line, len + 1);
	return (res);
}

static t_cmd_line	*_create_cmd_lines(char *line)
{
	int			len;
	t_cmd_line	*start;

	if (!line || !*line)
		return (NULL);
	if (*line == '|')
		line++;
	len = find_c('|', line);
	start = new_cmd_line();
	start->line = _dup_to_pipe(line, len);
	start->next = _create_cmd_lines(line + len);
	return (start);
}

// void test(t_cmd_line *cmd)
// {
// 	t_token *token;
// 	token = cmd->token;
// 	while (token)
// 	{
// 		printf("%s %d\n", token->word, token->type);
// 		token = token->next;
// 	}
// }

int	ft_parsing(t_struct *lst)
{
	int			x;
	char		*line;
	t_cmd_line	*cmd_line;

	lst->cmds = NULL;
	line = readline("minishell$> ");
	if (!line)
		ft_exit(*lst, NULL, lst->env);
	if (*line)
		add_history(line);
	x = check_pipes_good(lst, line);
	if (x)
	{
		free(line);
		return (x);
	}
	line = add_space(*lst, line);
	if (!line)
		return (x);
	cmd_line = _create_cmd_lines(line);
	free(line);
	create_token(cmd_line, lst);
	lst->cmd_line = cmd_line;
	return (0);
}
