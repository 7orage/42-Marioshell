#include "sig.h"

static void		hand_sigint(int	sig)
{
	(void)sig;
	
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();

}

static void	set_signal_handler(void)
{
	signal(SIGINT, hand_sigint);
}

int	main(int argc, char **argv, char **envnp)
{
	char	*line = NULL;

	(void)argc;
	(void)argv;
	(void)envnp;
	
	set_signal_handler();
	while (1) {
		line = readline("Minishell> ");
		add_history(line);
		free(line);
	}
}