#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

void	handle_sigint(int signal);
void	handle_sigquit(int signal);

int	main()
{
	char *line;
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_sigquit);

	line = readline("$ ");
	if (line != NULL)
		printf("%s\n", line);
	while (line && strcmp(line, "exit"))
	{
		line = readline("$ ");
		if (line != NULL)
			printf("%s\n", line);
	}
	return (0);
}
