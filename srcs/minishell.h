/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:34:26 by bbaudry           #+#    #+#             */
/*   Updated: 2021/11/21 19:46:19 by bbaudry          ###   ########.fr       */
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
# include <fcntl.h>
# include "./errors/errors.h"
# include "../includes/libft/libft.h"
# include <errno.h>
# include <string.h>
// # include "../minishell.h"

typedef enum e_err
{
	ERRNO_TO_STR = -1,
	UKN_ERR,
	MEM_ERR,
	QUOTE_ERR,
	BAD_FILE
	// NB_ARG,
	// FILE_FRMT,
	// READ_ERR,
	// CLOSEMAP_ERR,
	// MAP_CFG,
	// BADCHAR_ERR,
	// NOE_ERR,
	// NOP_ERR,
	// NOC_ERR,
}		t_err;

typedef struct s_error
{
	t_err	u_id;
	char	*msg;
}		t_error;

typedef struct s_struct
{
	t_list	*cmds;
	char	***env;
}		t_struct;
int	error(t_err raised, t_struct lst, char *line, int critical);
char *ft_pwd_in(char **cmd_parts, char ***env);

char    	**ft_split(char const *s, char c);
int     	ft_strncmp(const char *s1, const char *s2, size_t n);
int     	ft_echo(char **cmd_parts, char ***env);
int     	ft_cd(char **cmd_parts, char ***env);
int     	ft_pwd(char **cmd_parts, char ***env);
int     	ft_export(char **cmd_parts, char ***env);
int     	ft_unset(char **cmd_parts, char ***env);
int     	ft_env(char **cmd_parts, char ***env);
int     	ft_exit(char **cmd_parts, char ***env);
size_t  	ft_strlen(const char *s);
void    	ft_putstr_fd(char *s, int fd);
void    	ft_free(char **cmd_parts);
int     	select_cmd(t_struct lst, char **cmd_parts);
int     	ft_run(t_struct lst);
t_struct	ft_parsing(t_struct lst);
void		lst_free(t_struct);
char		*change_line(char *line, int opt);
void		handle_sigint(int signal);
void		handle_sigquit(int signal);
char		*var_gestion(t_struct lst, char *line);
char		**first_env(char **env);
void    	free_array_content(void **array);
void		clear_env(char ***env);
int			str_array_size(char **array);
int			ft_unsetenv(char ***env, char *name);
int			ft_setenv(char ***env, char *string);
int 		do_fork(char **cmd_parts);
char		*v_itoa(int n);
#endif
