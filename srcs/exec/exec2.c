#include "../minishell.h"

int	found_arg(t_cmd_line *cmd)
{
	t_token	*token;

	token = cmd->token;
	while (token)
	{
		if (token->type == ARG)
			return (1);
		token = token->next;
	}
	return (0);
}