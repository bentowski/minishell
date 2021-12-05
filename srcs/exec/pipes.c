/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/28 18:38:04 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/05 02:47:45 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (token->type == ARG)
			token = create_token2(token->word, token, token->next);
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

void	close_all(t_cmd_line *cmd)
{
	t_cmd_line	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->file[0] != 0)
			close(tmp->file[0]);
		if (tmp->file[1] != 1)
			close(tmp->file[1]);
		tmp = tmp->next;
	}
}

// static pid_t	ft_childs(int in, int out, t_struct lst, t_cmd_line *cmd_line)
// {
// 	pid_t	pid;
// 	int		x;

// 	x = 0;
// 	if (cmd_line->file[1] != 1)
// 		out = cmd_line->file[1];
// 	pid = fork();
// 	if (!pid)
// 	{
// 		dup2(in, 0);
// 		dup2(out, 1);
// 		close_all(lst.cmd_line);
// 		if (in != 0)
// 			close(in);
// 		if (out != 1)
// 			close(out);
// 		select_cmd(lst, cmd_line);
// 		exit(EXIT_SUCCESS);
// 	}
// 	else
// 	{	
// 		if (in != 0)
// 			close(in);
// 		if (out != 1)
// 			close(out);
// 		//waitpid(pid, &x, 0);
// 		return (pid);
// 	}
// }

int	**init_fd_tab(int len)
{
	int		i;
	int		**tab;

	tab = malloc(sizeof(int *) * (len + 1));
	i = 0;
	while (i < len)
		tab[i++] = malloc(sizeof(int) * 2);
	tab[i] = NULL;
	return (tab);
}

void	fd_free(int **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	openpipe(t_cmd_line *cmd, int len)
{
	t_cmd_line *tmp;
	int	i;
	int	**fd;

	fd = init_fd_tab(len);
	i = 0;
	tmp = cmd;
	while (tmp)
	{
		pipe(fd[i]);
		if (!i)
			tmp->fd[0] = 0;
		else
			tmp->fd[0] = fd[i-1][0];
		if (!tmp ->next)
		{
			close(fd[i][0]);
			close(fd[i][1]);
			tmp->fd[1] = 1;
		}
		else
			tmp->fd[1] = fd[i][1];
		tmp = tmp->next;
		i++;
	}
	fd_free(fd);
}

void	putfile(t_cmd_line *cmd)
{
	t_cmd_line	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->file[0] != 0)
			tmp->fd[0] = tmp->file[0];
		if (tmp->file[1] != 1)
			tmp->fd[1] = tmp->file[1];
		tmp = tmp->next;
	}
}

void	execcmd(t_cmd_line *cmd, t_struct *lst, int i, pid_t *pid)
{
	int	ret;
	printf("new child %d\n", i);
	pid[i] = fork();
	if(!pid[i])
	{
		dup2(cmd->fd[0], 0);
		dup2(cmd->fd[1], 1);
		close_all(cmd);
		ret = select_cmd(*lst, cmd);
		exit(ret);
	}
	if (cmd->fd[1] != 1)
		close(cmd->fd[1]);
	if (cmd->fd[0] != 0)
		close(cmd->fd[0]);

}

static int	ft_pipes(int n, t_struct *lst)
{
	int	i;
	t_cmd_line	*tmp;
	pid_t	*pid;
	int	ret;
	
	i = -1;
	tmp = lst->cmd_line;
	openpipe(tmp, n);
	putfile(tmp);
	pid = malloc(sizeof(pid_t) * n);
	while (++i < n)
	{
		execcmd(tmp, lst, i, pid);
	}
	i = 0;
	while (i < n)
	{
		waitpid(pid[i++], &ret, 0);
		//if (WIFEXITED(ret))
		//	ret = WEXITSTATUS(ret);
		printf("test%d\n", ret);	
	}
	free(pid);
	return (ret);
}

int	single_exec(t_struct *lst)
{
	dup2(lst->cmd_line->file[0], 0);
	dup2(lst->cmd_line->file[1], 1);
	close_all(lst->cmd_line);
	return(select_cmd(*lst, lst->cmd_line));
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
			return (ft_pipes(cmd_count(lst->cmd_line), lst));
		}
		else
		{
			close_all(lst->cmd_line);
			waitpid(pid, &ret, 0);
			if (WIFEXITED(ret))
				ret = (((ret) & 0xff00) >> 8);
			printf("main parent%d\n", ret);	
		}
	}
	else
		return (single_exec(lst));
	return (ret);
}
