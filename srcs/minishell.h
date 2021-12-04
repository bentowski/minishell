/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:34:26 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/04 01:33:30 by bbaudry          ###   ########.fr       */
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

typedef enum e_err
{
	ERRNO_TO_STR = -1,
	UKN_ERR,
	MEM_ERR,
	QUOTE_ERR,
	NO_VAR,
	BAD_ARG,
	BAD_FILE,
	TOO_MUCH,
	NON_NUM_FOUND
}		t_err;

typedef enum	e_filetype
{
	NONE,
	ARG,
	FILE_IN,
	HERE_DOC,
	FILE_OUT,
	FILE_OUT_APPEND,
	OPEN_FILE,
	LIMITER,
	OUT_FILE,
	OUT_FILE_APPEND
}	t_filetype;

typedef struct s_token
{
	char			*word;
	t_filetype		type;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd_line
{
	char				*line;
	t_token				*token;
	struct s_cmd_line	*next;
	char				**arg;
	int					file[2];
	int					here_doc_flag;
	char				*here_doc_content;
	char				*limiter;
	int					expanded;
}	t_cmd_line;

typedef struct s_error
{
	t_err	u_id;
	char	*msg;
}		t_error;

typedef struct s_struct
{
	t_list	*cmds;
	t_cmd_line	*cmd_line;
	char	***env;
	int		here_doc_flag;
	char	*here_doc_content;
	char	*limiter;
	char	*path;
	int		exit_status;
	int		is_child;
}		t_struct;

int			check_long_n(char *s);
int			error(t_err raised, t_struct *lst, char *line, int critical);
char		*ft_pwd_in(void);
char		*get_exit_status(t_struct *lst);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_echo(t_struct lst, char **cmd_parts, char ***env);
int			ft_cd(t_struct lst, char **cmd_parts, char ***env);
int			ft_pwd(t_struct lst, char **cmd_parts, char ***env);
int			ft_export(t_struct lst, char **cmd_parts, char ***env);
int			ft_unset(t_struct lst, char **cmd_parts, char ***env);
int			ft_env(t_struct lst, char **cmd_parts, char ***env);
int			ft_exit_bi(t_struct lst, char **cmd_parts, char ***env);
int			ft_exit(t_struct lst, char **cmd_parts, char ***env);
size_t		ft_strlen(const char *s);
void		ft_putstr_fd(char *s, int fd);
void		ft_free(char **cmd_parts);
char		*get_path(void *cmd, char ***env);
int			select_cmd(t_struct lst, t_cmd_line *cmd);
int			ft_run(t_struct *lst);

/* parsing */
char		*add_space(char *s);
void		skip_quote(char *res, char *s, int *x, int *y);
t_struct	ft_parsing(t_struct lst);

/* cmd_line utils */
t_cmd_line	*new_cmd_line(void);
t_cmd_line	*del_one_cmd_line(t_cmd_line *cmd_line);
void		del_cmd_list(t_cmd_line **cmd);
char		**token_join(t_token *token);

/* token utils */
t_token		*new_token(void);
t_token		*del_one_token(t_token *token);
void		del_token_list(t_token **token);
int			create_token(t_cmd_line *cmd);
t_token		*remove_word_token(t_token *token);


void		lst_free(t_struct lst);
char		**custom_split(char *s);
char		*change_line(char *line, int opt);
void		handle_sigint(int signal);
void		handle_sigquit(int signal);
char		*var_gestion(t_struct lst, char *line);
char		**first_env(char **env);
void		free_array_content(void **array);
void		clear_env(char ***env);
int			str_array_size(char **array);
int			ft_unsetenv(char ***env, char *name);
int			ft_setenv(char ***env, char *string);
int			do_fork(t_cmd_line *cmd);
char		*clean_join(char *s1, char *s2);
char		*v_itoa(int n);
char		*ft_get_env(char *str, char **env);
char		*third_lecture(char *line);

/* here_doc */

char		*here_doc_read(t_struct *lst);
int			here_doc_exec(char *path, t_struct lst, char **cmd_part,
				char ***env);

#endif
