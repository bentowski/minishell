/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 18:38:04 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/05 02:27:48 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../errors/errors.h"
#include "../minishell.h"

static int	gestion_file(t_struct *lst, t_cmd_line *cmd, t_token *token)
{
	t_token	*next;

	if (!token)
		return (0);
	next = token->next;
	if (token->type == FILE_IN || token->type == HERE_DOC
		|| token->type == FILE_OUT || token->type == FILE_OUT_APPEND)
		token = remove_word_token(token);
	else
	{
		token->word = var_gestion(*lst, token->word);
		token->word = third_lecture(token->word);
		if (token->type == OPEN_FILE)
		{
			if (cmd->file[0] != 0)
				close(cmd->file[0]);
			cmd->file[0] = open(token->word, O_RDONLY);
			if (cmd->file[0] < 0)
				return (error(BAD_FILE, lst, token->word, 0));
		}
		else if (token->type == OUT_FILE)
		{
			if (cmd->file[1] != 1)
				close(cmd->file[1]);
			cmd->file[1] = open(token->word, O_CREAT | O_WRONLY | O_TRUNC, 402);
			if (cmd->file[1] < 0)
				return (error(BAD_FILE, NULL, token->word, 0));
		}
		else if (token->type == OUT_FILE_APPEND)
		{
			if (cmd->file[1] != 1)
				close(cmd->file[1]);
			cmd->file[1] = open(token->word, O_APPEND | O_WRONLY | O_CREAT, 402);
			if (cmd->file[1] < 0)
				return (error(BAD_FILE, NULL, token->word, 0));
		}
		if (token->type == OPEN_FILE || token->type == OUT_FILE || token->type == OUT_FILE_APPEND)
		{
			cmd->here_doc_flag = 0;
			token = remove_word_token(token);
		}
		else if (token->type == LIMITER)
		{
			token = remove_word_token(token);
			cmd->here_doc_flag = 1;
		}
	}
	return (gestion_file(lst, cmd, next));
}

static int	cmd_count(t_cmd_line *cmds)
{
	t_cmd_line	*ptr;
	int		x;

	x = 0;
	ptr = cmds;
	while (ptr)
	{
		x++;
		ptr = ptr->next;
	}
	return (x);
}

static int	ft_childs(int in, int out, t_struct lst, t_cmd_line *cmd_line)
{
	pid_t	pid;
	int		x;

	x = 0;
	if (cmd_line->file[1] != 1)
		out = cmd_line->file[1];
	pid = fork();
	if (pid == 0)
	{
		if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		select_cmd(lst, cmd_line);
		exit(EXIT_SUCCESS);
	}
	else
	{
		waitpid(pid, &x, 0);
		return (1);
	}
}

static int	ft_pipes(int n, t_struct lst)
{
	int		in;
	int		i[2];
	int		fd[2];
	int		ret;
	t_cmd_line	*tmp;

	tmp = lst.cmd_line;
	in = tmp->file[0];
	i[0] = 0;
	while (i[0] < n - 1)
	{
		pipe(fd);
		ft_childs(in, fd[1], lst, tmp);
		in = fd[0];
		close(fd[1]);
		i[0] += 1;
		tmp = tmp->next;
		i[1] = gestion_file(&lst, tmp, tmp->token);
		if (i[1])
			return (i[1]);
	}
//	dup2(1, 1);
	dup2(in, 0);
	dup2(tmp->file[1], 1);
	ret = select_cmd(lst, tmp);
	return (ret);
}

int	ft_run(t_struct *lst)
{
	int		ret;
	int		pid;

	here_doc_checker(lst);
	gestion_file(lst, lst->cmd_line, lst->cmd_line->token);
	lst->is_child = 0;
	if (cmd_count(lst->cmd_line) > 1 || do_fork(lst->cmd_line))
	{
		pid = fork();
		if (pid == 0)
		{
			lst->is_child = 1;
			return (ft_pipes(cmd_count(lst->cmd_line), *lst));
		}
		else
		{
			waitpid(pid, &ret, 0);
			if (WIFEXITED(ret))
				ret = (((ret) & 0xff00) >> 8);
		}
	}
	else
		return (ft_pipes(cmd_count(lst->cmd_line), *lst));
	return (ret);
}
