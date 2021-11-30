#include "../minishell.h"

char *get_exit_status(t_struct *lst)
{
    return (v_itoa(lst->exit_status));
}