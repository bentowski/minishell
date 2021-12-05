/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 17:21:03 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/05 00:32:09 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	char	**new_env(char ***env, char *var)
{
	int		i;
	char	**new_env;

	i = 0;
	new_env = malloc(sizeof(char *) * (str_array_size(*env) + 2));
	if (!new_env)
		return (NULL);
	while ((*env)[i])
	{
		new_env[i] = (*env)[i];
		i++;
	}
	new_env[i] = ft_strdup(var);
	if (!new_env[i])
	{
		free(new_env);
		return (NULL);
	}
	new_env[i + 1] = NULL;
	free(*env);
	return (new_env);
}

int	ft_unsetenv(char ***env, char *name)
{
	int	i;
	int	len;

	if (!name || ft_strchr(name, '='))
		return (-1);
	i = 0;
	len = ft_strlen(name);
	while ((*env)[i] && (ft_strncmp((*env)[i], name, len)
		|| (*env)[i][len] != '='))
		i++;
	if (!(*env)[i])
		return (0);
	free((*env)[i]);
	while ((*env)[i])
	{
		(*env)[i] = (*env)[i + 1];
		i++;
	}
	return (0);
}

int	ft_setenv(char ***env, char *string)
{
	char	*name;
	int		len;
	int		i;

	if (!ft_strchr(string, '='))
		return (0);
	len = ft_strchr(string, '=') - string;
	name = malloc(sizeof(char) * (len + 2));
	if (!name)
		return (-1);
	ft_strlcpy(name, string, len + 2);
	i = 0;
	while ((*env)[i] && (ft_strncmp((*env)[i], name, len + 1)))
		i++;
	free(name);
	if ((*env)[i])
	{
		free((*env)[i]);
		(*env)[i] = ft_strdup(string);
	}
	else
		(*env) = new_env(env, string);
	if (!(*env))
		return (-1);
	return (0);
}

char	**first_env(char **env)
{
	char	**tmp_env;
	int		i;

	i = 0;
	tmp_env = ft_calloc(1, sizeof(char *) * (str_array_size(env) + 1));
	if (!tmp_env)
		return (0);
	while (env[i])
	{
		tmp_env[i] = ft_strdup(env[i]);
		if (!tmp_env[i])
		{
			free_array_content((void **)tmp_env);
			free(tmp_env);
			return (0);
		}
		i++;
	}
	tmp_env[i] = NULL;
	return (tmp_env);
}
