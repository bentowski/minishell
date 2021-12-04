/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:08:12 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/03 17:08:24 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_pwd_in(void)
{
	char	*buf;
	size_t	len;

	len = 0;
	buf = malloc(len * sizeof(char));
	if (!buf)
		return (NULL);
	while (getcwd(buf, len) == NULL)
	{
		free(buf);
		len++;
		buf = malloc(len * sizeof(char));
		if (!buf)
			return (NULL);
	}
	return (buf);
}

int	ft_pwd(t_struct lst, char **cmd_parts, char ***env)
{
	char	*buf;
	size_t	len;

	(void)env;
	(void)cmd_parts;
	len = 0;
	buf = malloc(len * sizeof(char));
	if (!buf)
		return (error(MEM_ERR, NULL, NULL, 0));
	while (getcwd(buf, len) == NULL)
	{
		free(buf);
		len++;
		buf = malloc(len * sizeof(char));
		if (!buf)
			return (error(MEM_ERR, NULL, NULL, 0));
	}
	ft_putstr_fd(buf, 1);
	write(1, "\n", 1);
	free(buf);
	if (lst.is_child)
		ft_exit(lst, cmd_parts, lst.env);
	return (0);
}
