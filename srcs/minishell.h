/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:34:26 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/06 08:48:53 by bbaudry          ###   ########.fr       */
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
# include "../includes/libft/libft.h"
# include <errno.h>
# include <string.h>

typedef enum e_err
{
	ERRNO_TO_STR = -1,
	UKN_ERR,
	MEM_ERR,
	BAD_FILE,
	QUOTE_ERR,
	NO_VAR,
	BAD_ARG,
	TOO_MUCH,
	LON_PIPE,
	NON_NUM_FOUND,
	NO_ALPH,
	NO_PERM
}		t_err;

typedef enum e_filetype
{
	NONE,
	ARG,
	FILE_IN,
	H_D,
	FILE_OUT,
	FILE_OUT_APP,
	IN_F,
	LIM,
	OUT_F,
	OUT_F_APP
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
	int					fd[2];
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
	t_list		*cmds;
	t_cmd_line	*cmd_line;
	char		***env;
	int			here_doc_flag;
	char		*here_doc_content;
	char		*limiter;
	char		*path;
	int			exit_status;
	int			is_child;
	int			startin;
	int			startout;
	pid_t		pid;
}		t_struct;

/* ================================= Builtins =============================== */
/* === echo === */
int			check_long_n(char *s);
int			ft_echo(t_struct lst, char **cmd_parts, char ***env);

/* === pwd === */
int			ft_pwd(t_struct lst, char **cmd_parts, char ***env);
char		*ft_pwd_in(void);

/* === cd === */
int			ft_cd(t_struct lst, char **cmd_parts, char ***env);

/* === unset === */
int			ft_unset(t_struct lst, char **cmd_parts, char ***env);

/* === export === */
int			ft_export(t_struct lst, char **cmd_parts, char ***env);

/* === env === */
int			ft_env(t_struct lst, char **cmd_parts, char ***env);

/* === exit === */
int			ft_exit_bi(t_struct lst, char **cmd_parts, char ***env);
int			ft_exit(t_struct lst, char **cmd_parts, char ***env);
int			non_num_found(char *s);

/* ================================= Clear ================================== */
void		lst_free(t_struct lst);
void		free_array_content(void **array);
void		ft_free(char **cmd_parts);

/* ================================= Errors ================================= */
int			error(t_err raised, t_struct *lst, char *line, int critical);
char		*v_itoa(int n);
void		ft_putstr_fd(char *s, int fd);

/* ================================= Env ==================================== */
int			ft_setenv(char ***env, char *string);
int			ft_unsetenv(char ***env, char *name);
int			str_array_size(char **array);
char		*ft_get_env(char *str, char **env);
char		**first_env(char **env);
void		clear_env(char ***env);

/* ================================= Parsing ================================ */
int			check_pipes_good(t_struct *lst, char *line);
int			ft_parsing(t_struct *lst);
int			check_pipes_good(t_struct *lst, char *line);
char		*add_space(t_struct lst, char *s);
char		*get_exit_status(t_struct *lst);
char		*third_lecture(char *line);
void		skip_quote(char *res, char *s, int *x, int *y);

/* === vars_gestion === */
char		*var_gestion(t_struct lst, char *line);
char		**get_vars_names(char *line, char **vars_name);
char		*get_new_line(t_struct lst, char *line, char **vars_name);
int			get_new_lenght(t_struct lst, char *line,
				char **vars_name, char **env);

/* ================================= Run ==================================== */
int			do_fork(t_cmd_line *cmd);
int			select_cmd(t_struct lst, t_cmd_line *cmd);
int			ft_run(t_struct *lst);
char		*get_path(void *cmd, char ***env);

/* ================================= Signaux ================================ */
void		handle_sigint(int signal);
void		handle_sigquit(int signal);
void		handle_sigint_ii(int signal);
void		handle_sigquit_ii(int signal);

/* ================================= OTHER ================================== */
/* cmd_line utils */
char		**token_join(t_token *token);
void		del_cmd_list(t_cmd_line **cmd);
t_cmd_line	*new_cmd_line(void);
t_cmd_line	*del_one_cmd_line(t_cmd_line *cmd_line);

/* token utils */
int			create_token(t_cmd_line *cmd, t_struct *lst);
void		del_token_list(t_token **token);
t_token		*create_token2(char *s, t_token	*start,
				t_token *next, t_struct *lst);
t_token		*del_one_token(t_token *token);
t_token		*new_token(char *s);
t_token		*remove_word_token(t_token *token);

/* here_doc */
int			here_doc_checker(t_struct *lst);
int			here_doc_exec(char *path, t_struct lst, char **cmd_part,
				char ***env);
char		*here_doc_read(t_struct *lst, t_cmd_line *cmd);

/* pseudo libft */
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		**custom_split(char *s, t_struct *lst);
char		*change_line(char *line, int opt);
char		*clean_join(char *s1, char *s2);
char		**ft_split(char const *s, char c);
size_t		ft_strlen(const char *s);

int			ft_pipes(int n, t_struct *lst);
int			no_pipe(t_struct *lst);

void		close_all(t_cmd_line *cmd);

void		fd_free(int **tab);

int			**init_fd_tab(int len);
int			gestion_file(t_struct *lst);

#endif
