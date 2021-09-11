/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_part_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 13:34:31 by bbaudry           #+#    #+#             */
/*   Updated: 2021/09/11 12:58:54 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_echo(char **cmd_parts, char **env)
{
    int x;
    int n;

    if (!(cmd_parts[1]))
    {
        // error(N_ERR, to_free, fatale or not)
        return (-1);
    }
    x = 1;
    n = ft_strncmp(cmd_parts[1], "-n", 2);
    if (n == 0)
        x = 2;
    while (cmd_parts[x])
    {
        ft_putstr_fd(cmd_parts[x++], 1);
        if (cmd_parts[x])
          write(1, " ", 1);
    }
    if (n != 0)
        write(1, "\n", 1);
    return (1);
}

int cd_base(char **cmd_parts, int lenght, char *buf)
{
    char *new;
    int len;
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < 3)
    if (buf[x++] == '/')
      y++;
    y = -1;
    if (!(new = malloc((x - 1) * sizeof(char))))
        return (-1);
        //error(N_ERR, to_free, fatale or not)
    while (++y < x)
    new[y] = buf[y];
    chdir(new);
    free(new);
    return (1);
}

int cd_relative(char **cmd_parts, char *buf, size_t len)
{
    char *target;
    int x;
    int y;

    if (!(target = malloc(len + ft_strlen(cmd_parts[1]))))
        return (-1);
        //error(N_ERR, to_free, fatale or not)
    x = 0;
    while (buf[x])
    {
        target[x] = buf[x];
        x++;
    }
    y = 0;
    while (cmd_parts[1][y])
    {
        target[x + y + 1] = cmd_parts[1][y];
        y++;
    }
    target[x + y] = '\0';
    if (chdir(target) == -1)
        return (-1);
        //error(N_ERR, to_free, fatale or not)
    return (0);
}

int ft_cd(char **cmd_parts, char **env)
{
    char *buf;
    size_t len;

    len = 0;
    if (!(buf = malloc(len * sizeof(char))))
        return (-1);
        //error(N_ERR, to_free, fatale or not)
    while (getcwd(buf, len) == NULL)
    {
        free(buf);
        if (!(buf = malloc(len * sizeof(char))))
            return (-1);
            //error(N_ERR, to_free, fatale or not)
        len++;
    }
    if (cmd_parts[1] == NULL)
    {
        if (cd_base(cmd_parts, len, buf) != 1)
            return (-1);
            //error(N_ERR, to_free, fatale or not)
    }
    else if (cmd_parts[2] != NULL)
        return (-1);
        //error(N_ERR, to_free, fatale or not)
    else if (chdir(cmd_parts[1]) == -1)
        if (cd_relative(cmd_parts, buf, len) == -1)
        {
            printf("%s : no such file or directory\n", cmd_parts[1]);
            free(buf);
            return (-1);
            //error(N_ERR, to_free, fatale or not)
        }
    free(buf);
    return (1);
}

int ft_pwd(char **cmd_parts, char **env)
{
    char *buf;
    size_t len;

    len = 0;
    if (!(buf = malloc(len * sizeof(char))))
        return (-1);
        //error(N_ERR, to_free, fatale or not)
    while (getcwd(buf, len) == NULL)
    {
        free(buf);
        if (!(buf = malloc(len * sizeof(char))))
            return (-1);
            //error(N_ERR, to_free, fatale or not)
        len++;
    }
    ft_putstr_fd(buf, 1);
    write(1, "\n", 1);
    free(buf);
    return (1);
}

int ft_env(char **cmd_parts, char **env)
{
    int i;

    i = 0;
    while (env[i])
        printf("%s\n", env[i++]);
    return (1);
}

int ft_export(char **cmd_parts, char **env)
{
    return (1);
}

int ft_unset(char **cmd_parts, char **env)
{
    return (1);
}

int ft_exit(char **cmd_parts, char **env)
{
    //ft_free
    return (0);
}
