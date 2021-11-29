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
    free(line);
    free(lst->limiter);
    lst->limiter = NULL;
    return (content);
}

int here_doc_exec(char  *path, t_struct lst, char **cmd_part, char ***env)
{
    int fd[2];
    pid_t pid;
    //char *arg[] = {"", NULL};

    pipe(fd);
    pid = fork();
    if (!pid)
    {
        close(fd[0]);
        dup2(fd[1], 1);
        write(1, lst.here_doc_content, ft_strlen(lst.here_doc_content));
        free(path);
        lst_free(lst);
        exit (0);
    }
    else
    {
        close(fd[1]);
        dup2(fd[0], 0);
        printf("%s\n", path);
        return (execve(path, cmd_part, *env));
    }
}