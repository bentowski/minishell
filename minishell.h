#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

char		**ft_split(char const *s, char c);
char    *get_next_line(int fd, char **line);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int ft_echo(char **cmd_parts);
int ft_cd(char **cmd_parts);
int ft_pwd(char **cmd_parts);
int ft_export(char **cmd_parts);
int ft_unset(char **cmd_parts);
int ft_env(char **cmd_parts);
int ft_exit(char **cmd_parts);
size_t ft_strlen(const char *s);
void	ft_putstr_fd(char *s, int fd);
void ft_free(char ***cmd_parts);

#endif
