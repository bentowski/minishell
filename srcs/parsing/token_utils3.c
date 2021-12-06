/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 11:25:08 by vgallois          #+#    #+#             */
/*   Updated: 2021/12/06 11:25:09 by vgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
