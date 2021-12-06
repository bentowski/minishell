/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <vgallois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 08:45:54 by vgallois          #+#    #+#             */
/*   Updated: 2021/12/06 09:41:30 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_env(char *str, char **env)
{
	int	i;
	int	x;
	int	y;

	i = -1;
	while (env[++i])
	{
		x = ft_strchr(env[i], '=') - env[i];
		y = ft_strlen(str);
		if (x < y)
			x = y;
		if (ft_strncmp(str, env[i], x) == 0)
			return (ft_strdup(&env[i][ft_strlen(str) + 1]));
	}
	return (NULL);
}

int	ft_exit(t_struct lst, char **cmd_parts, char ***env)
{
	ft_free(*env);
	rl_clear_history();
	del_cmd_list(&lst.cmd_line);
	(void)cmd_parts;
	if (!lst.is_child)
		printf("Bye bye 😎\n");
	exit(lst.exit_status);
}

static char	*get_path_deux(char **possible, char *end_path)
{
	int			x;
	char		*tmp;
	char		*ret;
	struct stat	sb;

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
	return (NULL);
}

char	*get_path(void *cmd, char ***env)
{
	char	**possible;
	char	*path_line;
	char	*ret;
	int		x;

	(void)env;
	path_line = ft_get_env("PATH", *env);
	if (!path_line)
		return (NULL);
	possible = ft_split(path_line, ':');
	free(path_line);
	ret = get_path_deux(possible, cmd);
	x = 0;
	while (possible[x])
		free(possible[x++]);
	free(possible);
	x = 0;
	return (ret);
}

int	non_num_found(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (!isdigit(s[i]))
			return (1);
	return (0);
}
