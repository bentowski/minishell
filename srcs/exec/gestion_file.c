/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <vgallois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 06:08:58 by vgallois          #+#    #+#             */
/*   Updated: 2021/12/06 09:37:35 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	_open_close(t_token *token, t_cmd_line *cmd)
{
	if (token->type == IN_F)
	{
		if (cmd->file[0] != 0)
			close(cmd->file[0]);
		cmd->file[0] = open(token->word, O_RDONLY);
	}
	else if (token->type == OUT_F)
	{
		if (cmd->file[1] != 1)
			close(cmd->file[1]);
		cmd->file[1] = open(token->word, O_CREAT | O_WRONLY | O_TRUNC, 402);
	}
	else if (token->type == OUT_F_APP)
	{
		if (cmd->file[1] != 1)
			close(cmd->file[1]);
		cmd->file[1] = open(token->word, O_APPEND | O_WRONLY | O_CREAT, 402);
	}
}

int	_gestion_file(t_struct *lst, t_cmd_line *cmd, t_token *t)
{
	t_token	*next;

	if (!t)
		return (0);
	next = t->next;
	if (!(t->type == FILE_IN || t->type == H_D || t->type == FILE_OUT
			|| t->type == FILE_OUT_APP))
	{
		t->word = var_gestion(*lst, t->word);
		if (t->type == ARG)
			t = create_token2(t->word, t, t->next, lst);
		t->word = third_lecture(lst, t->word);
		if (t->type == IN_F || t->type == OUT_F || t->type == OUT_F_APP)
		{
			_open_close(t, cmd);
			if ((t->type == IN_F && cmd->file[0] < 0) || ((t->type == OUT_F
						|| t->type == OUT_F_APP) && cmd->file[1] < 0))
				return (error(BAD_FILE, lst, t->word, 0));
		}
		if (t->type == IN_F || t->type == OUT_F || t->type == OUT_F_APP)
			cmd->here_doc_flag = 0;
		else if (t->type == LIM)
			cmd->here_doc_flag = 1;
	}
	return (_gestion_file(lst, cmd, next));
}

int	gestion_file(t_struct *lst)
{
	int			ret;
	t_cmd_line	*tmp;

	tmp = lst->cmd_line;
	while (tmp)
	{
		ret = _gestion_file(lst, tmp, tmp->token);
		if (ret)
			return (ret);
		tmp = tmp->next;
	}
	return (0);
}
