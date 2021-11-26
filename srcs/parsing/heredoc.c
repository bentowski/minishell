#include "../minishell.h"
#include "../../includes/libft/libft.h"

static int  ft_strcmp(const char *s1, const char *s2)
{
    int i;

    if (!s1 && !s2)
        return (0);
    if (!s1)
        return (*s2);
    if (!s2)
        return (*s1);
    i = 0;
    while (s1[i] && s1[i] == s2[i])
        i++;
    return (s1[i] - s2[i]);
}

char *here_doc_read(t_struct *lst)
{
    char    *content;
    char    *line;
    char    *tmp;
    char    *tmp2;

    if (lst->here_doc_content)
        free(lst->here_doc_content);
    content = ft_strdup("");
    if (!content)
        return (NULL);
    line = readline("here_doc> ");
    while (ft_strcmp(line, lst->limiter))
    {
        tmp = ft_strjoin(line, "\n");
        tmp2 = ft_strjoin(content, tmp);
        free(content);
        free(tmp);
        free(line);
        content = tmp2;
        line = readline("here_doc> ");
    }
    content = var_gestion(*lst, content);
    printf("%s", content);
    free(line);
    free(lst->limiter);
    lst->limiter = NULL;
    return (content);
}