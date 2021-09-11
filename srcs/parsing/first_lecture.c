/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   first_lecture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:02:45 by bbaudry           #+#    #+#             */
/*   Updated: 2021/09/11 13:27:24 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *first_part_4(char *new, char *line, char **vars_name)
{
    char *tmp;
    int x;
    int y;
    int i;
    int lenght;

    x = 0;
    y = 0;
    lenght = 0;
    while (line[x])
    {
        if (line[x] == 34)
        {
            x++;
            while (line[x] && line[x] != 34)
            {
                if (line[x] == '$')
                {
                    i = 0;
                    tmp = getenv(vars_name[lenght]);
                    if (tmp)
                    {
                        while (tmp[i])
                            new[y++] = tmp[i++];
                    }
                    x++;
                    while (line[x] && line[x] != ' ' && line[x] != '$' && line[x] != 34)
                        x++;
                }
                else
                    new[y++] = line[x++];
            }
            x++;
        }
        else if (line[x] == '$')
        {
            i = 0;
            tmp = getenv(vars_name[lenght]);
            if (tmp)
            {
                while (tmp[i])
                    new[y++] = tmp[i++];
            }
            x++;
            while (line[x] && line[x] != ' ' && line[x] != '$')
                x++;
        }
        else
            new[y++] = line[x++];
    }
    new[y] = '\0';
    return (new);
}


static char *first_part_3(char *new, char *line, char **vars_name)
{
    int x;
    int y;
    int lenght;

    y = 0;
    x = 0;
    while (line[x])
    {
        if (line[x] == 34)
        {
            x++;
            if (line[x++] == '$')
            {
                lenght = 0;
                while (line[x] && line[x] != ' ' && line[x] != '$' && line[x] != 34)
                {
                    vars_name[y][lenght++] = line[x++];
                }
                vars_name[y][lenght] = '\0';
                y++;
            }
            x++;
        }
        else if (line[x++] == '$')
        {
            lenght = 0;
            while (line[x] && line[x] != ' ' && line[x] != '$')
            {
                vars_name[y][lenght++] = line[x++];
            }
            vars_name[y][lenght] = '\0';
            y++;
        }
    }
    x = 0;
    lenght = 1;
    while (line[x])
    {
        if (line[x] == 34)
        {
            while (line[x] && line[x] != 34)
            {
                lenght++;
                x++;
            }
        }
        else
            lenght++;
        x++;
    }
    x = 0;
    while (vars_name[x])
        if (getenv(vars_name[x++]))
            lenght += ft_strlen(getenv(vars_name[x - 1]));
    new = malloc(sizeof(char) * lenght);
    if (new)
        return (new = first_part_4(new, line, vars_name));
    return (NULL);
}

static char *first_part_2(char *line, char **vars_name)
{
    char *new;
    int x;
    int y;
    int lenght;

    x = 0;
    y = 0;
    while (line[x])
    {
        if (line[x] == 34)
        {
            x++;
            while (line[x] && line[x] != 34)
            {
                if (line[x] == '$')
                {
                    lenght = 0;
                    while (line[++x] && line[x] != ' ' && line[x] != '$' && line[x] != 34)
                        lenght++;
                    vars_name[y] = malloc(sizeof(char) * (lenght + 1));
                    if (!vars_name[y++])
                        return (NULL);
                }
                else
                    x++;
            }
        }
        else if (line[x] == '$')
        {
            lenght = 0;
            while (line[++x] && line[x] != ' ' && line[x] != '$')
                lenght++;
            vars_name[y] = malloc(sizeof(char) * (lenght + 1));
            if (!vars_name[y++])
                return (NULL);
        }
        else
            x++;
    }
    new = first_part_3(new, line, vars_name);
    return (new);
}

char *first_lecture(char *line)
{
    char *new;
    char **vars_name;
    int lenght;
    int x;

    lenght = 0;
    x = 0;
    while (line[x])
    {
        if (line[x] == 34)
        {
            x++;
            while (line[x] && line[x] != 34)
            {
                if (line[x] == '$')
                    lenght++;
                x++;
            }
        }
        else if (line[x++] == '$')
            lenght++;
    }
    vars_name = NULL;
    if (lenght > 0)
    {
        vars_name = malloc(sizeof(char *) * (lenght + 1));
        if (!vars_name)
        {
            free(line);
            return (NULL);
        }
        vars_name[lenght] = NULL;
        new = first_part_2(line, vars_name);
        free(line);
        ft_free(vars_name);
        return (new);
    }
    return (line);
}
