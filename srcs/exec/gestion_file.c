/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 06:08:58 by vgallois          #+#    #+#             */
/*   Updated: 2021/12/06 06:09:00 by vgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	gestion_file(t_struct *lst, t_cmd_line *cmd, t_token *token)
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