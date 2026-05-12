#include "minishell.h"

// compiler avce -lreadline

int	main(int argc, char **argv, char **envnp)
{
	char	*line = NULL;

	(void)argc;
	(void)argv;
	(void)envnp;
	
	while (1) {
		line = readline("Minishell> ");
		add_history(line);
		free(line);
	}
}