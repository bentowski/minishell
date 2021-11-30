#include "minishell.h"

int main(int argc, char **argv, char **env)
{
  t_struct lst;
  int end;
  int ret;

  (void)argc;
  (void)argv;
  signal(SIGINT, handle_sigint);
  signal(SIGQUIT, handle_sigquit);
  end = 0;
  env = first_env(env);
  lst.env = &env;
  lst.here_doc_flag = 0;
  lst.here_doc_content = 0;
  lst.limiter = NULL;
  lst.exit_status = 0;
  while (end == 0)
  {
    lst = ft_parsing(lst);
    lst.here_doc_flag = 0;
    if (lst.cmds)
    {
        ret = ft_run(&lst);
        if (ret == -1)
            end = 1;
		    else
          lst.exit_status = ret;
      if (lst.here_doc_content)
      {
        free(lst.here_doc_content);
        lst.here_doc_content = NULL;
      }
    }
    lst_free(lst);
  }
  ft_free(env);
  rl_clear_history();
//  printf("%d\n", ret);
  return (ret);
}
