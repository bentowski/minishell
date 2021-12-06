/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/05 02:26:40 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/06 06:00:49 by vgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	_add_token_back(t_token **lst, t_token *new)
{
	t_token	*tmp;

	tmp = *lst;
	if (!tmp)
	{
		*lst = new;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static t_filetype	_assign_type(t_token *token, t_filetype prec)
{
	if (prec == FILE_IN)
		token->type = OPEN_FILE;
	else if (prec == HERE_DOC)
		token->type = LIMITER;
	else if (prec == FILE_OUT)
		token->type = OUT_FILE;
	else if (prec == FILE_OUT_APPEND)
		token->type = OUT_FILE_APPEND;
	if (!ft_strncmp(token->word, "<", 2))
		token->type = FILE_IN;
	else if (!ft_strncmp(token->word, "<<", 3))
		token->type = HERE_DOC;
	else if (!ft_strncmp(token->word, ">", 2))
		token->type = FILE_OUT;
	else if (!ft_strncmp(token->word, ">>", 3))
		token->type = FILE_OUT_APPEND;
	if (token->type == NONE)
		token->type = ARG;
	if ((prec == FILE_IN && token->type != OPEN_FILE)
		|| (prec == FILE_OUT && token->type != OUT_FILE)
		|| (prec == FILE_OUT_APPEND && token->type != OUT_FILE_APPEND)
		|| (prec == HERE_DOC && token->type != LIMITER))
		token->type = NONE;
	return (token->type);
}

int	create_token(t_cmd_line *cmd)
{
	char		**tab;
	t_token		*new;
	int			i;
	t_filetype	prec;

	if (!cmd)
		return (0);
	tab = custom_split(cmd->line);
	prec = NONE;
	i = 0;
	while (tab[i])
	{
		new = new_token();
		new->word = tab[i++];
		prec = _assign_type(new, prec);
		if (prec == NONE)
			exit(printf("caca %s \n", new->word));//mettre error parsing < <file
		_add_token_back(&cmd->token, new);
	}
	free(tab);
	tab = NULL;
	return (create_token(cmd->next));
}

t_token	*create_token2(char *s, t_token	*start, t_token *next)
{
	char	**tab;
	t_token	*new;
	int		i;

	if (!s)
		return (start);
	tab = custom_split(s);
	start->word = tab[0];
	i = 1;
	if (tab[1])
	{
		start->next = NULL;
		while (tab[i])
		{
			new = new_token();
			new->type = ARG;
			new->word = tab[i++];
			_add_token_back(&start, new);
		}
		new->next = next;
	}
	free(s);
	free(tab);
	tab = NULL;
	return (start);
}
// free tab[i] ?

t_token	*remove_word_token(t_token *token)
{
	if (!token)
		return (NULL);
	if (token->word)
	{
		free(token->word);
		token->word = NULL;
	}
	return (token);
}
