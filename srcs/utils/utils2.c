/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgallois <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 08:43:57 by vgallois          #+#    #+#             */
/*   Updated: 2021/12/06 08:43:58 by vgallois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	int	i;

	if (!s1 && !s2)
		return (0);
	if (!s1)
		return (*s2);
	if (!s2)
		return (*s1);
	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	check_long_n(char *s)
{
	int	x;

	x = 0;
	while (s[x])
		if (s[x++] != 'n')
			return (0);
	return (1);
}

int	do_fork(t_cmd_line *cmd)
{
	t_token	*tmp;
	char	*builtin[6];
	int		x;

	tmp = cmd->token;
	while (tmp && !tmp->word)
		tmp = tmp->next;
	builtin[0] = "cd";
	builtin[1] = "pwd";
	builtin[2] = "env";
	builtin[3] = "export";
	builtin[4] = "unset";
	builtin[5] = "exit";
	x = -1;
	while (++x < 6)
		if (!ft_strncmp(tmp->word, builtin[x], ft_strlen(builtin[x]) + 1))
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
