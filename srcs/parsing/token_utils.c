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
	*token =NULL;
}

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

static void	_add_token_back(t_token **lst, t_token *new)
{
	t_token	*tmp;
	if (!lst)
		return ;
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
		|| (prec == FILE_OUT_APPEND && token->type !=OUT_FILE_APPEND)
		|| (prec == HERE_DOC && token->type != LIMITER))
		token->type = NONE;
	return (token->type);
}

int	create_token(t_cmd_line *cmd)
{
	char	**tab;
	t_token	*new;
	int	i;
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
		printf("%s %d %d\n", new->word, new->type, prec);
		if (prec == NONE)
			exit(printf("caca %s \n", new->word));//mettre error parsing < <file
		_add_token_back(&cmd->token, new);
	}
	free(tab);// ne pas free les tab[i] psk ils sont stockes dans les token
	tab = NULL;
	return (create_token(cmd->next));
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
		if (tmp->word)
			res[i++] = tmp->word;
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
}
