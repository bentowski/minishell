/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <vgallois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:59:22 by vgallois          #+#    #+#             */
/*   Updated: 2021/12/03 16:56:20 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../../includes/libft/libft.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (*s2);
	if (!s2)
		return (*s1);
	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*here_doc_read(t_struct *lst, t_cmd_line *cmd)
{
	char	*content;
	char	*line;
	char	*tmp;

	if (!cmd->here_doc_content)
	{
		free(cmd->here_doc_content);
		cmd->here_doc_content = NULL;
	}
	content = ft_strdup("");
	if (!content || !cmd->limiter)
		return (NULL);
	line = readline("here_doc> ");
	while (ft_strcmp(line, cmd->limiter))
	{
		tmp = ft_strjoin(line, "\n");
		content = clean_join(content, tmp);
		free(line);
		line = readline("here_doc> ");
	}
	if (!cmd->expanded)
		content = var_gestion(*lst, content);
	free(line);
	free(cmd->limiter);
	cmd->limiter = NULL;
	cmd->here_doc_content = content;
	return (tmp);
}

int	here_doc_exec(char *path, t_struct lst, char **cmd_part, char ***env)
{
	int		fd[2];
	pid_t	pid;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		write(1, lst.here_doc_content, ft_strlen(lst.here_doc_content));
		free(path);
		lst_free(lst);
		exit (0);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		return (execve(path, cmd_part, *env));
	}
}

int	_found_quote(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] == '"' || s[i] == '\'')
			return (1);
	return (0);
}

int	here_doc_checker(t_struct *lst)
{
	t_cmd_line	*tmp;
	t_token		*token;

	tmp = lst->cmd_line;
	while (tmp)
	{
		token = tmp->token;
		while (token)
		{
			if (token->type == HERE_DOC)
				token = remove_word_token(token);
			else if (token->type == LIMITER)
			{
				tmp->limiter = ft_strdup(token->word);
				tmp->expanded = _found_quote(tmp->limiter);
				tmp->limiter = third_lecture(tmp->limiter);
				if (!here_doc_read(lst, tmp))
					return (1);
			}
			token = token->next;
		}
		tmp = tmp->next;
	}
	return (0);
}