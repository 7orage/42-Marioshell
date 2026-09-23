#include "minishell.h"

/*
hand_hd		-> CTRL-C INSIDE A HEREDOC: CLOSE STDIN SO readline GIVES UP
sig_heredoc	-> HANDLERS WHILE READING A HEREDOC
*/

static void	hand_hd(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	close(STDIN_FILENO);
}

void	sig_heredoc(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = hand_hd;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}
