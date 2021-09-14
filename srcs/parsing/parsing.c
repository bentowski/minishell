/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 12:49:29 by bbaudry           #+#    #+#             */
/*   Updated: 2021/09/14 10:27:35 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

t_struct ft_parsing(t_struct lst)
{
    int x;
    char *line;
    char **cmds;

    lst.cmds = NULL;
    line = readline("minishell $>");
    if (!line)
    {
        rl_clear_history();
        exit(EXIT_SUCCESS);
    }
    add_history(line);
    line = first_lecture(line);
    if (!line)
        return (lst);
    line = second_lecture(line);
    cmds = ft_split(line, 124);
    free(line);
    x = -1;
    while (cmds[++x])
        ft_lstadd_back(&lst.cmds, ft_lstnew(cmds[x], 0, 1));
    // ft_lstadd_back(&lst.cmds, NULL);
    ft_free(cmds);
    return (lst);
}
