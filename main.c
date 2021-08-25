#include "minishell.h"

int select_cmd(char **cmd_parts)
{
  int (*functions[7])(char **cmd_parts);
  int len;
  int x;
  char *cmd;
  char *lst[8] = { "echo", "cd", "pwd", "export", "unset", "env", "exit" };

  functions[0] = ft_echo;
  functions[1] = ft_cd;
  functions[2] = ft_pwd;
  functions[3] = ft_export;
  functions[4] = ft_unset;
  functions[5] = ft_env;
  functions[6] = ft_exit;
  if (cmd_parts[0])
  {
    x = -1;
    len = ft_strlen(cmd_parts[0]);
    while (lst[++x])
      if (ft_strncmp(cmd_parts[0], lst[x], len) == 0)
      {
        printf("%s\n", "ENTREE");

        return ((*functions[x])(cmd_parts));
      }
  }
  return (-1);
}

char *change_line(char *line)
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
  if (!(new = malloc(ft_strlen(line) * sizeof(char))))
    return (NULL);
  while (line[x])
  {
    if (line[x] == '"')
    {
      x++;
      while (line[x] && line[x++] != '"')
      {
            new[y++] = line[x - 1];
        }
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

int main()
{
  char *line;
  char **cmd_parts;
  char separator;
  int x;

  separator = 10;
  // separator = 32;
  while (1)
  {
    x = 0;
    write(1, "minishell $> ", 13);
    cmd_parts = NULL;
    get_next_line(0, &line);
    line = change_line(line);
    cmd_parts = ft_split(line, separator);
    printf("%s\n", line);
    // printf("%s\n", cmd_parts[0]);
    free(line);
    // while (cmd_parts[x])
    // {
    //   printf("%s\n", cmd_parts[x]);
    //   x++;
    // }
    // printf("%s\n", cmd_parts[x]);
    if (select_cmd(cmd_parts) == 0)
      break;
    ft_free(&cmd_parts);
  }
  ft_free(&cmd_parts);
  return (EXIT_SUCCESS);
}
