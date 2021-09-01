/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 12:49:29 by bbaudry           #+#    #+#             */
/*   Updated: 2021/09/01 21:11:12 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *change_line(char *line, int opt)
{
    char *new;
    int p;
    int x;
    int y;

    x = 0;
    y = 0;
    p = 1;
    if (!(line))
        return (NULL);
    if (!(new = malloc(sizeof(char)*(ft_strlen(line) + 1))))
        return (NULL);
    while (line[x])
    {
        if (line[x] == '"')
        {
            x++;
            while (line[x] && line[x++] != '"')
                new[y++] = line[x - 1];
        }
        if (line[x] == 39)
        {
            x++;
            while (line[x] && line[x++] != 39)
                new[y++] = line[x - 1];
        }
        if (line[x++] == ' ')
            new[y++] = '\n';
        else
            new[y++] = line[x - 1];
    }
    new[y] = '\0';
    free(line);
    return (new);
}

static char *second_lecture(char *line)
{
    char *new;
    int x;
    int y;

    if (!(new = malloc(sizeof(char)*(ft_strlen(line) + 1))))
        return (NULL);
    x = 0;
    y = 0;
    while (line[x])
    {
        if (line[x + 1] && line[x + 1] == '|')
        {
            x++;
            new[y++] = line[x++];
            x++;
        }
        else
            new[y++] = line[x++];
    }
    new[y] = '\0';
    free(line);
    return (new);
}

char *first_lecture(char *line)
{
    char *new;
    char **vars_name;
    int count;
    int x;
    int y;

    count = 0;
    x = 0;
    while (line[x])
        if (line[x++] == '$')
            count++;
    x = -1;
    if (count > 0)
    {
        vars_name = malloc(sizeof(char *) * count);
        if (!vars_name)
            return (NULL);
        y = 0;
        while (line[++x])
        {
            count = 0;
            if (line[x] == '$')
            {
                while (line[x] && line[x] != ' ' && line[x] != '$')
                {
                    count++;
                    x++;
                }
                vars_name[y] = malloc(sizeof(char) * (count + 1));
                if (!vars_name[y])
                    return (NULL);
                y++;
            }
        }
        y = 0;
        x = 0;
        while (line[x])
        {
            count = 0;
            if (line[x++] == '$')
            {
                while (line[x] && line[x] != ' ' && line[x] != '$')
                    vars_name[y][count++] = line[x++];
                vars_name[y][count] = '\0';
                y++;
            }
        }
        x = 0;
        while (vars_name[x])
        {
            printf("var : %s\n", vars_name[x++]);
            free(vars_name[x]);
        }
        free(vars_name);
    }
    // while (line[++x])
    // {
    //     if (line[x] == '$')
    //     {
    //         tmp = x;
    //         while (line[x] != ' ')
    //             size++;
    //         break;
    //     }
    // }
    // ft_free(vars_name);
    return (line);
}

t_struct ft_parsing(t_struct lst)
{
    int x;
    char *line;
    char **cmds;

    lst.cmds = NULL;
    cmds = NULL;
    line = readline("minishell $>");
	if (line != NULL)
		printf("%s\n", line);
    // line = first_lecture(line);
    line = second_lecture(line);
    cmds = ft_split(line, 124);
    free(line);
    x = -1;
    while (cmds[++x])
        ft_lstadd_back(&lst.cmds, ft_lstnew(cmds[x]));
    ft_free(cmds);
    return (lst);
}
