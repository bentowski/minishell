/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 06:02:03 by vgallois          #+#    #+#             */
/*   Updated: 2021/12/06 06:02:23 by vgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*new_token(void)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	new->next = NULL;
	new->word = NULL;
	new->type = NONE;
	return (new);
}

t_token	*del_one_token(t_token *token)
/* free 1 token and return token->next (can be NULL) */
{
	t_token	*next;

	if (!token)
		return (NULL);
	next = token->next;
	if (token->word)
	{
		free(token->word);
		token->word = NULL;
	}
	free(token);
	token = NULL;
	return (next);
}

void	del_token_list(t_token **token)
{
	t_token	*tmp;

	tmp = *token;
	while (tmp)
		tmp = del_one_token(tmp);
	*token = NULL;
}

static int	_token_count(t_token *token)
{
	if (!token)
		return (0);
	if (token->word)
		return (_token_count(token->next) + 1);
	else
		return (_token_count(token->next));
}

char	**token_join(t_token *token)
{
	int		len;
	char	**res;
	t_token	*tmp;
	int		i;

	len = _token_count(token);
	res = malloc(sizeof(char *) * (len + 1));
	tmp = token;
	i = 0;
	while (tmp)
	{
		if (tmp->type == ARG)
			res[i++] = tmp->word;
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
}
