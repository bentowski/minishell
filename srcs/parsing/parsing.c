/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbaudry <bbaudry@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 12:49:29 by bbaudry           #+#    #+#             */
/*   Updated: 2021/12/01 14:51:51 by vgallois         ###   ########.fr       */
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
        error(MEM_ERR, &lst, NULL, 1);
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

int	_nb_space(char *s)
{
	int	len;

	len = 0;
	while (*s)
	{
		if (*s == '<' || *s == '>')
			len++;
		if (*s == '|')
			len += 2;
		s++;
	}
	return (len);
}

static char	*_add_space(char *s)
{
	char	*res;
	int		len;
	int		i;
	int		j;

	len = _nb_space(s) + ft_strlen(s);
	res = malloc(sizeof(char) * (len + 1));
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '<' || s[i] == '>')
		{
			res[j++] = ' ';
			res[j++] = s[i++];
			if (s[i] == '<' || s[i] == '>')
				res[j++] = s[i++];
		}
		else if (s[i] == '|')
		{
			res[j++] = ' ';
			res[j++] = s[i++];
			res[j++] = ' ';
		}
		else
			res[j++] = s[i++];
	}
	printf("%s\n", res);
	res[j] = 0;
	free(s);
	return (res);
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
	line = _add_space(line);
    line = var_gestion(lst, line);
	if (!line)
        return (lst);
    line = pipe_gestion(lst, line);
    cmds = ft_split(line, '|');
    free(line);
    x = -1;
	// attention si ft_lstnew est nUULL gros soucis
    while (cmds[++x])
        ft_lstadd_back(&lst.cmds, ft_lstnew(cmds[x], 0, 1));
    ft_free(cmds);
    return (lst);
}
