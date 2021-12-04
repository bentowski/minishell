/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 12:49:29 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/03 17:32:56 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../errors/errors.h"

static char	*pipe_gestion(t_struct lst, char *line)
{
	char	*new;
	int		x;
	int		y;

	new = malloc(sizeof(char) * (ft_strlen(line) + 1));
	if (!new)
		error(MEM_ERR, &lst, NULL, 1);
	x = 0;
	y = 0;
	while (line[x])
	{
		if (line[x + 1] && line[x + 1] == '|')
		{
			x++;
			new[y++] = line[x++];
			x++;
		}
		else
			new[y++] = line[x++];
	}
	new[y] = '\0';
	free(line);
	return (new);
}

int	find_c(char c, char *s)
{
	int	i;

	if (!s)
		return (-1);
	i = -1;
	while (s[++i])
		if (s[i] == c)
			return (i);
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
		line++;//check si *line == 0
	len = find_c('|', line);
	start = new_cmd_line();
	start->line = _dup_to_pipe(line, len);
	start->next = _create_cmd_lines(line + len);
	return (start);
}

void	testcmd(t_cmd_line *cmd)
{
	t_token	*token;
	if (!cmd)
		return ;
	printf("cmd: %s\n", cmd->line);
	token = cmd->token;
	while (token)
	{
		printf("token: %s\n", token->word);
		token = token->next;
	}
	testcmd(cmd->next);
}

t_struct	ft_parsing(t_struct lst)
{
	int		x;
	char	*line;
	char	**cmds;
	t_cmd_line *cmd_line;


	lst.cmds = NULL;
	line = readline("minishell $>");
	if (!line)
	{
		ft_free(*lst.env);
		exit(EXIT_SUCCESS);
	}
	add_history(line);
	line = add_space(line);
//	line = var_gestion(lst, line);
	if (!line)
		return (lst);
	line = pipe_gestion(lst, line);
	cmds = ft_split(line, '|');
	cmd_line = _create_cmd_lines(line);
	free(line);
	create_token(cmd_line);
	testcmd(cmd_line);
	del_cmd_list(&cmd_line);
	x = -1;
	while (cmds[++x])
		ft_lstadd_back(&lst.cmds, ft_lstnew(cmds[x], 0, 1));
	ft_free(cmds);
	return (lst);
}
