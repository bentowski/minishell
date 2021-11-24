/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_gestion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 19:02:45 by bbaudry           #+#    #+#             */
/*   Updated: 2021/11/24 15:10:52 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../errors/errors.h"

// 34 = '
// 39 = "

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
            in = -in;
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
    x = 0;
    while (vars_name[x])
        if (getenv(vars_name[x++]))
            lenght += ft_strlen(getenv(vars_name[x - 1]));
    return (lenght);
}

static char *first_part_4(t_struct lst, char *new, char *line, char **vars_name)
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
    lenght = get_new_lenght(line, vars_name, in);
    new = malloc(sizeof(char) * lenght);
    if (!new)
        error(MEM_ERR, lst, NULL, 1);
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
                    while ((line[x] >= 'A' && line[x] <= 'Z') ||
                    (line[x] >= 'a' && line[x] <= 'z'))
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
            while ((line[x] >= 'A' && line[x] <= 'Z') ||
                (line[x] >= 'a' && line[x] <= 'z'))
                x++;
        }
        else
            new[y++] = line[x++];
    }
    new[y] = '\0';
    return (new);
}

static char *test(char *line, char *voidline, int *xvalue)
{
    char *new;
    int lenght;
    int x;

    x = *xvalue;
    new = voidline;
    lenght = 0;
    while ((line[x] >= 'A' && line[x] <= 'Z') ||
        (line[x] >= 'a' && line[x] <= 'z'))
        new[lenght++] = line[x++];
    new[lenght] = '\0';
    *xvalue = x;
    return (new);
}

static char *take_vars_names_bis(t_struct lst, char *new_line, char *line, char **vars_name)
{
    int x;
    int y;
    int in;

    x = 0;
    y = 0;
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
            while (line[x] && line[x] != 34)
                if (line[x++] == '$')
                {
                    vars_name[y] = test(line, vars_name[y], &x);
                    y++;
                }
        }
        else if (line[x++] == '$')
        {
            vars_name[y] = test(line, vars_name[y], &x);
            y++;
        }
    }
    return (first_part_4(lst, new_line, line, vars_name));
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
        while ((line[++tmpx] >= 'A' && line[tmpx] <= 'Z') ||
            (line[tmpx] >= 'a' && line[tmpx] <= 'z'))
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

static char *tab_fill(t_struct lst, char *line, char **vars_name)
{
    char *new_line;
    int x;
    int y;
    int lenght;
    int in;

    x = 0;
    y = 0;
    in = 1;
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
    new_line = take_vars_names_bis(lst, new_line, line, vars_name);
    return (new_line);
}

static int var_count(t_struct lst, char *line)
{
    int x;
    int ret;

    x = -1;
    ret = 0;
    while (line[++x])
        if (line[x] == 39)
        {
            x++;
            while (line[x] != 39)
                if (!line[x++])
                    return (error(QUOTE_ERR, lst, NULL, 0));
        }
        else if (line[x] == 34)
        {
            x++;
            while (line[x] && line[x] != 34)
                if (line[x++] == '$')
                    ret++;
            if (!line[x])
                return (error(QUOTE_ERR, lst, NULL, 0));
        }
        else if (line[x] == '$')
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
        new_line = tab_fill(lst, line, vars_tab);
        free(line);
        ft_free(vars_tab);
        return (new_line);
    }
    return (line);
}
