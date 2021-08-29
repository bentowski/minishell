#include "minishell.h"

char *change_line(char *line, int opt)
{
    char *new;
    int p;
    int x;
    int y;

    x = 0;
    y = 0;
    p = 1;
    if (!(line))
        return (NULL);
    if (!(new = malloc(sizeof(char)*(ft_strlen(line) + 1))))
        return (NULL);
    if (opt == 1)
    {
        while (line[x])
        {
            if (line[x + 1] && line[x + 1] == '|')
            {
                x++;
                new[y++] = line[x++];
                x++;
            }
            else
                new[y++] = line[x++];
        }
    }
    while (line[x])
    {
        if (line[x] == '"')
        {
            x++;
            while (line[x] && line[x++] != '"')
                new[y++] = line[x - 1];
        }
        if (line[x] == 39)
        {
            x++;
            while (line[x] && line[x++] != 39)
                new[y++] = line[x - 1];
        }
        if (line[x++] == ' ')
            new[y++] = '\n';
        else
            new[y++] = line[x - 1];
    }
    new[y] = '\0';
    free(line);
    return (new);
}

int main(int argc, char **argv, char **env)
{
  char *line;
  char **cmds;
  char separator;
  int x;
  t_struct lst;

  separator = 124;
  while (1)
  {
    write(1, "minishell $> ", 13);
    cmds = NULL;
    get_next_line(0, &line);
    line = change_line(line, 1);
    cmds = ft_split(line, separator);
    free(line);
    lst.cmds = NULL;
    x = 0;
    while (cmds[x])
    {
        ft_lstadd_back(&lst.cmds, ft_lstnew(cmds[x]));
        x++;
    }
    if (lst.cmds)
    {
        if (lst.cmds->next)
        {
            ft_pipe(lst, env);
        }
        else
        {
            if (select_cmd(lst, env, 1) == 0)
                break;
        }
    }
    ft_free(cmds);
    lst_free(lst);
  }
  ft_free(cmds);
  lst_free(lst);
  return (EXIT_SUCCESS);
}
