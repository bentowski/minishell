/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:34:26 by bbaudry           #+#    #+#             */
/*   Updated: 2021/09/10 11:28:50 by jfoucher         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "../includes/libft/libft.h"

typedef struct s_struct
{
	int		file[2];
	t_list	*cmds;
}		t_struct;

char    **ft_split(char const *s, char c);
int     ft_strncmp(const char *s1, const char *s2, size_t n);
int     ft_echo(char **cmd_parts, char **env);
int     ft_cd(char **cmd_parts, char **env);
int     ft_pwd(char **cmd_parts, char **env);
int     ft_export(char **cmd_parts, char **env);
int     ft_unset(char **cmd_parts, char **env);
int     ft_env(char **cmd_parts, char **env);
int     ft_exit(char **cmd_parts, char **env);
size_t  ft_strlen(const char *s);
void    ft_putstr_fd(char *s, int fd);
void    ft_free(char **cmd_parts);
int     select_cmd(t_struct lst, char **env, int opt);
int     ft_pipe(t_struct lst, char **env);
t_struct	ft_parsing(t_struct lst);
void	lst_free(t_struct);
char *change_line(char *line, int opt);
void	handle_sigint(int signal);
void	handle_sigquit(int signal);
char	*first_lecture(char *line);
char	**first_env(char **env);
void    free_array_content(void **array);
void	clear_env(char **env);
int		str_array_size(char **array);
int		ft_unsetenv(char **env, char *name);
int		ft_setenv(char **env, char *string);

#endif
