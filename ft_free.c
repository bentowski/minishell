#include "minishell.h"

void ft_free(char ***cmd_parts)
{
  int x;
  char **tmp;

  x = -1;
  tmp = *cmd_parts;
  while (tmp[++x])
    free(tmp[x]);
  free(tmp);
}
