/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 11:59:22 by vgallois          #+#    #+#             */
/*   Updated: 2021/12/01 12:07:31 by vgallois         ###   ########.fr       */
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

char	*here_doc_read(t_struct *lst)
{	
	char	*content;
	char	*line;
	char	*tmp;

	if (!lst->here_doc_content)
		lst->here_doc_content = ft_strdup("");
	content = ft_strdup("");
	if (!content)
		return (NULL);
	line = readline("here_doc> ");
	while (ft_strcmp(line, lst->limiter))
	{
		tmp = ft_strjoin(line, "\n");
		content = clean_join(content, tmp);
		free(line);
		line = readline("here_doc> ");
	}
	content = var_gestion(*lst, content);
	lst->here_doc_content = clean_join(lst->here_doc_content, content);
	free(line);
	free(lst->limiter);
	lst->limiter = NULL;
	return (lst->here_doc_content);
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
