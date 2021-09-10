#include "minishell.h"

void ft_free(char **cmd_parts)
{
  int x;
  char **tmp;

  x = -1;
  tmp = cmd_parts;
  while (tmp[++x])
    free(tmp[x]);
  free(tmp);
}

void	lst_free(t_struct lst)
{
	t_list	*tmp;
	t_list	*fr;

	tmp = lst.cmds;
	while (tmp)
	{
		fr = tmp->next;
        printf("tmp->content : %s\n", tmp->content);
        free(tmp->content);
		free(tmp);
		tmp = fr;
	}
    free(tmp);
}
