#include "minishell.h"

/*
hand_sigint	-> CTRL-C ON THE PROMPT: NEW LINE AND NEW PROMPT
sig_prompt	-> HANDLERS WHILE WAITING FOR A LINE
sig_exec	-> THE SHELL GOES DEAF WHILE A CHILD IS RUNNING
sig_child	-> THE CHILD GOES BACK TO THE DEFAULT BEHAVIOUR
sig_msg		-> WHAT THE SHELL PRINTS WHEN A LINE ENDED ON A SIGNAL

g_signal only ever holds a signal number.
*/

volatile sig_atomic_t	g_signal = 0;

static void	hand_sigint(int sig)
{
	g_signal = sig;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	sig_prompt(void)
{
	signal(SIGINT, hand_sigint);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_exec(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	sig_child(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	sig_msg(int status)
{
	if (status == 128 + SIGINT)
		write(2, "\n", 1);
	else if (status == 128 + SIGQUIT)
		write(2, "Quit (core dumped)\n", 19);
}
