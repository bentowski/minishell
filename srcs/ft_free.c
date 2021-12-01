#include "minishell.h"

void ft_free(char **cmd_parts)
{
	int x;
	char **tmp;

	x = -1;
	if (!cmd_parts)
		return ;
	tmp = cmd_parts;
	while (tmp[++x])
	{
		free(tmp[x]);
		tmp[x] = NULL;
	}
	free(tmp);
	tmp = NULL;
}

void	lst_free(t_struct lst)
{
	t_list	*tmp;
	t_list	*fr;
	int		i;

	i = 0;
	tmp = lst.cmds;
	// if (lst.env)
	// {
	// 	while (lst.env[i])
	// 		free(lst.env[i++]);
	// 	free(lst.env);
	// }
	while (tmp)
	{
		fr = tmp->next;
        free(tmp->content);
		free(tmp);
		tmp = fr;
	}
}
