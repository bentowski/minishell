/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 12:49:29 by bbaudry           #+#    #+#             */
/*   Updated: 2021/09/28 13:40:06 by bbaudry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../errors/errors.h"

static char *pipe_gestion(t_struct lst, char *line)
{
    char *new;
    int x;
    int y;

    if (!(new = malloc(sizeof(char)*(ft_strlen(line) + 1))))
        error(MEM_ERR, lst, NULL, 1);
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
        ft_free(*lst.env);
        exit(EXIT_SUCCESS);
    }
    add_history(line);
    line = var_gestion(lst, line);
    if (!line)
        return (lst);
    line = pipe_gestion(lst, line);
    cmds = ft_split(line, 124);
    free(line);
    x = -1;
    while (cmds[++x])
        ft_lstadd_back(&lst.cmds, ft_lstnew(cmds[x], 0, 1));
    ft_free(cmds);
    return (lst);
}
