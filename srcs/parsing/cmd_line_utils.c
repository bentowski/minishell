#include "../minishell.h"

t_cmd_line	*new_cmd_line(void)
{
	t_cmd_line	*new;

	new = malloc(sizeof(t_cmd_line));
	if (!new)
		return (NULL);
	new->line = NULL;
	new->token = NULL;
	new->arg = NULL;
	new->file[0] = 0;
	new->file[1] = 1;
	new->here_doc_content = NULL;
	new->here_doc_flag = 0;
	new->next = NULL;
	return (new);
}

t_cmd_line	*del_one_cmd_line(t_cmd_line *cmd_line)
/* free cmd_line and return cmd_line->next (may be NULL) */
{
	t_cmd_line *next;

	if (!cmd_line)
		return (NULL);
	next = cmd_line->next;
	if (cmd_line->line)
	{
		free(cmd_line->line);
		cmd_line->line = NULL;
	}
	if (cmd_line->token)
		del_token_list(&cmd_line->token);
	cmd_line->token = NULL;
	if (cmd_line->arg)
		free(cmd_line->arg);
	if (cmd_line->here_doc_content)
		free(cmd_line->here_doc_content);
	free(cmd_line);
	cmd_line = NULL;
	return (next);
}

void	del_cmd_list(t_cmd_line **cmd)
{
	t_cmd_line	*tmp;

	tmp = *cmd;
	while (tmp)
		tmp = del_one_cmd_line(tmp);
	*cmd = NULL;
}