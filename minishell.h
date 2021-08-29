/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:34:26 by bbaudry           #+#    #+#             */
/*   Updated: 2021/08/28 21:14:35 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "libft/libft.h"
#include <sys/stat.h>

typedef struct s_struct
{
	int		file[2];
	t_list	*cmds;
}		t_struct;

char    **ft_split(char const *s, char c);
char    *get_next_line(int fd, char **line);
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
void	lst_free(t_struct);

#endif
