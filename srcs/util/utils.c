/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 10:25:52 by bbaudry           #+#    #+#             */
/*   Updated: 2021/11/30 15:45:24 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int do_fork(char **cmd_parts)
{
	char	*bltin[7] = { "echo", "cd", "pwd", "export", "unset", "env", "exit" };
	int		x;
	int		len;

    x = -1;
	len = ft_strlen(cmd_parts[0]);
	while (++x < 7)
		if (ft_strncmp(cmd_parts[0], bltin[x], ft_strlen(bltin[x]) + 1) == 0)
            return (1);
	return (0);
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

int ft_max(int i, int x)
{
	if (i < x)
		return (x);
	return (i);
}

char	*ft_get_env(char *str, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		if (ft_strncmp(str, env[i], ft_max((ft_strchr(env[i], '=') - env[i]), ft_strlen(str))) == 0)
			return (&env[i][ft_strlen(str) + 1]);
	return (NULL);
}
