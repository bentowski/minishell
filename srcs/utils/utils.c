/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 10:25:52 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/03 23:10:48 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int check_long_n(char *s)
{
	int x;

	x = 0;
	while (s[x])
		if (s[x++] != 'n')
			return (0);
	return (1);
}

int	do_fork(char **cmd_parts)
{
	char	*builtin[6];
	int		x;

	builtin[0] = "cd";
	builtin[1] = "pwd";
	builtin[2] = "env";
	builtin[3] = "export";
	builtin[4] = "unset";
	builtin[5] = "exit";
	x = -1;
	while (++x < 6)
		if (!ft_strncmp(cmd_parts[0], builtin[x], ft_strlen(builtin[x]) + 1))
			return (0);
	return (1);
}

static int	itoa_get_len(int n, int sign)
{
	int		len;

	len = sign + 1;
	while (n / 10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*v_itoa(int n)
{
	char	*res;
	int		len;
	int		sign;

	sign = 0;
	if (n < 0)
		sign = 1;
	len = itoa_get_len(n, sign);
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len--] = '\0';
	if (sign)
		res[0] = '-';
	while (len != (-1 + sign))
	{
		res[len] = "0123456789"[((n % 10))];
		if (sign)
			res[len] = "0123456789"[(-(n % 10))];
		n /= 10;
		len--;
	}
	return (res);
}

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
		if (x > y)
			x = y;
		if (ft_strncmp(str, env[i], x) == 0)
			return (ft_strdup(&env[i][ft_strlen(str) + 1]));
	}
	return (NULL);
}

char	*clean_join(char *s1, char *s2)
{
	char	*tmp;

	tmp = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (tmp);
}

char	*third_lecture(char *line)
{
	int		x;
	int		y;
	int		count;
	char	*new;

	x = 0;
	count = 0;
	while (line[x])
	{
		if (line[x] == 34)
		{
			x++;
			while (line[x] && line[x] != 34)
			{
				count++;
				x++;
			}
			if (!line[x])
				return (NULL);
			x++;
		}
		else if (line[x] == 39)
		{
			x++;
			while (line[x] && line[x] != 39)
			{
				count++;
				x++;
			}
			if (!line[x])
				return (NULL);
			x++;
		}
		else
		{
			count++;
			x++;
		}
	}
	new = malloc(sizeof(char) * (count + 1));
	if (!new)
		return (NULL);
	x = -1;
	y = 0;
	while (line[++x])
	{
		if (line[x] == 34)
			while (line[++x] && line[x] != 34)
				new[y++] = line[x];
		else if (line[x] == 39)
			while (line[++x] && line[x] != 39)
				new[y++] = line[x];
		else
			new[y++] = line[x];
	}
	new[y] = '\0';
	free(line);
	return (new);
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
	char	**i;
	char	*ret;
	int		x;

	(void)env;
	path_line = getenv("PATH");
	if (!path_line)
		return (NULL);
	path_line = ft_substr(path_line, 5, ft_strlen(path_line) - 5);
	possible = ft_split(path_line, ':');
	free(path_line);
	i = ft_split(cmd, ' ');
	ret = get_path_deux(possible, i[0]);
	x = 0;
	while (possible[x])
		free(possible[x++]);
	free(possible);
	x = 0;
	while (i[x])
		free(i[x++]);
	free(i);
	return (ret);
}
