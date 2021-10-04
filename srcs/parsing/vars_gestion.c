/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_gestion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:02:45 by bbaudry           #+#    #+#             */
/*   Updated: 2021/10/04 14:06:00 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../errors/errors.h"

static char *first_part_4(char *new, char *line, char **vars_name)
{
    char *tmp;
    int x;
    int y;
    int i;
    int lenght;
    int in;

    x = 0;
    y = 0;
    in = 1;
    lenght = 0;
    while (line[x])
    {
        if (line[x] == 39)
        {
            x++;
            in = -in;
        }
        if (line[x] == 34 && in > 0)
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

static int get_new_lenght(char *line, char **vars_name, int in)
{
    int lenght;
    int x;

    x = 0;
    lenght = 1;
    while (line[x])
    {
        if (line[x] == 39)
        {
            x++;
            printf("%d\n", in);
            in = -in;
            printf("%d\n", in);
        }
        else if (line[x] == 34 && in > 0)
        {
            x++;
            while (line[x] && line[x] != 34)
            {
                lenght++;
                x++;
            }
            x++;
        }
        else
            lenght++;
        x++;
    }
    printf("%d\n", lenght);
    x = 0;
    while (vars_name[x])
        if (getenv(vars_name[x++]))
            lenght += ft_strlen(getenv(vars_name[x - 1]));
    return (lenght);
}

static char *take_vars_values(t_struct lst, char *new_line, char *line, char **vars_name)
{
    int x;
    int y;
    int lenght;
    int in;

    y = 0;
    x = 0;
    in = 1;
    while (line[x])
    {
        if (line[x] == 39)
        {
            x++;
            in = -in;
        }
        else if (line[x] == 34 && in > 0)
        {
            x++;
            if (line[x++] == '$')
            {
                lenght = 0;
                while (line[x] && line[x] != ' ' && line[x] != '$' && line[x] != 34)
                    vars_name[y][lenght++] = line[x++];
                vars_name[y][lenght] = '\0';
                y++;
            }
            x++;
        }
        else if (line[x++] == '$')
        {
            lenght = 0;
            while (line[x] && line[x] != ' ' && line[x] != '$')
                vars_name[y][lenght++] = line[x++];
            vars_name[y][lenght] = '\0';
            y++;
        }
    }
    lenght = get_new_lenght(line, vars_name, in);
    new_line = malloc(sizeof(char) * lenght);
    if (!new_line)
        error(MEM_ERR, lst, NULL, 1);
    return (new_line = first_part_4(new_line, line, vars_name));
}

static char **malloc_names(t_struct lst, char *line, char **vars_name, int *x, int *y)
{
    int lenght;
    int tmpx;
    int ptry;

    tmpx = *x;
    ptry = *y;
    if (line[tmpx] == '$')
    {
        lenght = 0;
        while (line[++tmpx] && line[tmpx] != ' ' && line[tmpx] != '$')
            lenght++;
        vars_name[ptry] = malloc(sizeof(char) * (lenght + 1));
        if (!vars_name[ptry++])
            error(MEM_ERR, lst, NULL, 1);
    }
    else
        tmpx++;
    *x = tmpx;
    *y = ptry;
    return (vars_name);
}

static char *take_vars_names(t_struct lst, char *line, char **vars_name)
{
    char *new_line;
    int x;
    int y;
    int lenght;
    int in;

    x = 0;
    y = 0;
    in = 0;
    while (line[x])
    {
        if (line[x] == 39)
        {
            x++;
            in = -in;
        }
        else if (line[x] == 34 && in > 0)
            while (line[x + 1] && line[x + 1] != 34)
                vars_name = malloc_names(lst, line, vars_name, &x, &y);
        else
            vars_name = malloc_names(lst, line, vars_name, &x, &y);
    }
    new_line = take_vars_values(lst, new_line, line, vars_name);
    return (new_line);
}

static int var_count(t_struct lst, char *line)
{
    int x;
    int ret;

    x = 0;
    ret = 0;
    while (line[x])
        if (line[x] == 39)
        {
            x++;
            while (line[x] && line[x] != 39)
                x++;
            if (!line[x++])
                return (error(QUOTE_ERR, lst, NULL, 0));
        }
        else if (line[x] == 34)
        {
            x++;
            while (line[x] && line[x] != 34)
                if (line[x++] == '$')
                    ret++;
            if (!line[x++])
                return (error(QUOTE_ERR, lst, NULL, 0));
        }
        else if (line[x++] == '$')
            ret++;
    return (ret);
}

char *var_gestion(t_struct lst, char *line)
{
    char *new_line;
    char **vars_tab;
    int lenght;
    int x;

    lenght = var_count(lst, line);
    if (lenght < 0)
        return (NULL);
    vars_tab = NULL;
    if (lenght > 0)
    {
        vars_tab = malloc(sizeof(char *) * (lenght + 1));
        if (!vars_tab)
        {
            free(line);
            error(MEM_ERR, lst, NULL, 1);
        }
        vars_tab[lenght] = NULL;
        new_line = take_vars_names(lst, line, vars_tab);
        free(line);
        ft_free(vars_tab);
        return (new_line);
    }
    return (line);
}
