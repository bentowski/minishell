/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 08:45:54 by vgallois          #+#    #+#             */
/*   Updated: 2021/12/06 08:45:55 by vgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	char	*tmp;
	int		x;

	(void)env;
	path_line = ft_get_env("PATH", *env);
	if (!path_line)
		return (NULL);
	tmp = ft_substr(path_line, 5, ft_strlen(path_line) - 5);
	free(path_line);
	possible = ft_split(tmp, ':');
	free(tmp);
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
