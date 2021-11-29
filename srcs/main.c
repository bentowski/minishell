#include "minishell.h"

int main(int argc, char **argv, char **env)
{
  t_struct lst;
  int end;
  int ret;
  char	*tmp;
  char	*str;

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
        {
          tmp = v_itoa(ret);
          str = ft_strjoin("?=", tmp);
          free(tmp);
          ft_setenv(lst.env, str);
          free(str);
        }
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
  return (EXIT_SUCCESS);
}
