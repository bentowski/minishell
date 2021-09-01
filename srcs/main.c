#include "minishell.h"

int main(int argc, char **argv, char **env)
{
  t_struct lst;
  int end;

  signal(SIGINT, handle_sigint);
  signal(SIGQUIT, handle_sigquit);
  end = 0;
  while (end == 0)
  {
    // write(1, "minishell $> ", 13);
    lst = ft_parsing(lst);
    if (lst.cmds)
    {
        if (lst.cmds->next)
            ft_pipe(lst, env);
        else
            if (select_cmd(lst, env, 1) == 0)
                end = 1;
    }
    lst_free(lst);
  }
  return (EXIT_SUCCESS);
}
