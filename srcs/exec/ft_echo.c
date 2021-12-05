#include "../minishell.h"

int	ft_echo(t_struct lst, char **cmd_parts, char ***env)
{
	int		x;
	int		n;

	(void)env;
	n = 1;
	if ((cmd_parts[1]))
	{
		x = 0;
		while (cmd_parts[++x][0] == '-' && check_long_n(&cmd_parts[x][1]))
			n = -1;
		while (cmd_parts[x])
		{
			ft_putstr_fd(cmd_parts[x++], 1);
			if (cmd_parts[x])
				write(1, " ", 1);
		}
	}
	if (n != -1)
		write(1, "\n", 1);
	if (lst.is_child)
		ft_exit(lst, cmd_parts, env);
	return (0);
}
