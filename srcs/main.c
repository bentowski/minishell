#include "minishell.h"

int main(int argc, char **argv, char **env)
{
  t_struct lst;
  int end;
  int ret;

  signal(SIGINT, handle_sigint);
  signal(SIGQUIT, handle_sigquit);
  end = 0;
  env = first_env(env);
  lst.env = &env;
  while (end == 0)
  {
    lst = ft_parsing(lst);
    if (lst.cmds)
    {
        ret = ft_run(lst);
        if (ret == -1)
            end = 1;
    }
    lst_free(lst);
  }
  ft_free(env);
  rl_clear_history();
  return (EXIT_SUCCESS);
}
