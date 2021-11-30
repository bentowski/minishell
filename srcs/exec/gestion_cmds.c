/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:32:42 by bbaudry           #+#    #+#             */
/*   Updated: 2021/11/24 16:16:42 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*get_path_deux(char **possible, char *end_path)
{
	int		x;
	char	*tmp;
	char	*ret;
    struct stat sb;

	x = 0;
	while (possible[x])
	{
		tmp = ft_strjoin(possible[x], "/");
		ret = ft_strjoin(tmp, end_path);
		free(tmp);
		if (stat(ret, &sb) == 0)
			return (ret);
		free(ret);
		x++;
	}
	x = 0;
	// while (i[x])
	// 	free(i[x++]);
	// free(i);
	x = 0;
		printf("get_path2 possible %p %s\n", possible, possible[0]);

	return (NULL);
}
 // a refondre avec ndup(cmds, strchr(space)) au lieu du split s
static char	*get_path(void *cmd, char ***env)
{
	char	**possible;
	char	*path_line;
	char	**i;
	char	*ret;
	int		x;

	(void)env;
	path_line = getenv("PATH");
	if (!path_line)
		return (NULL);
	path_line = ft_substr(path_line, 5, ft_strlen(path_line) - 5);
	possible = ft_split(path_line, ':');
	printf("get_path possible %p %s\n", possible, possible[0]);
	free(path_line);
	i = ft_split(cmd, ' ');
	ret = get_path_deux(possible, i[0]);
	x = 0;
	while (possible[x])
	{
		//printf("%p\n", possible[x]);
		free(possible[x++]);
	}
	free(possible);
	x = 0;
	while (i[x])
		free(i[x++]);
	free(i);
	return (ret);
}
/*
static int get_name_exec(char *str)
{
	int x;

	x = ft_strlen(str);
	while (str[x] != '.')
		x--;
	return (x + 1);
}*/

static int ft_exec(t_struct lst, char **cmd_parts, char ***env)
{
	char *path;
	int ret;
	int x;

	ret = -1;
	x = 0;
	path = get_path(cmd_parts[0], env);
	printf("ft_exec path %s\n", path);
	// if (path == NULL)
	// {
	// 	// if (!(cmd_parts[0][0] == '.'))
	// 	// {
	// 		ft_free(cmd_parts);
	// 		return (1);
	// 	// }
	// 	// attention, si on mets "../philopopo/philosophers" ca ne fonctionne pas et n'affiche pas de msg \
	// 	//d'erreurs, pareil si on mets ./nimp ou ../nimp ou .nimp, plus de selection a avoir
	// 	// path = ft_strjoin(ft_pwd_in(cmd_parts, env), &cmd_parts[0][get_name_exec(cmd_parts[0])]);
	// }
	if (path)
	{
		if (lst.here_doc_flag)
			ret = here_doc_exec(path, lst, cmd_parts, env);
		else
			ret = execve(path, cmd_parts, *env);
		free(path);
	}
	printf("ft_exec\n");
	ft_free(cmd_parts);
	return (ret);
}

int select_cmd(t_struct lst, char **cmd_parts)
{
	char *bltin[8] = { "echo", "cd", "pwd", "export", "unset", "env", "exit" };
	int (*functions[7])(char **cmd_parts, char ***env);
	int x;
	int 	len;

	functions[0] = ft_echo;
	functions[1] = ft_cd;
	functions[2] = ft_pwd;
	functions[3] = ft_export;
	functions[4] = ft_unset;
	functions[5] = ft_env;
	functions[6] = ft_exit;
	x = -1;
	while (bltin[++x])
		if (ft_strncmp(cmd_parts[0], bltin[x], ft_strlen(bltin[x]) + 1) == 0)
		{
			len = (*functions[x])(cmd_parts, lst.env);
			ft_free(cmd_parts);
			return (len);
		}
	return (ft_exec(lst, cmd_parts, lst.env));
}
