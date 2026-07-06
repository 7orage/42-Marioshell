#include "signaux.h"

static void		hand_sigint(int	sig)
{
	(void)sig;
	
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0); 
	rl_redisplay();
}

static void		hand_sigquit(int sig) // TO ADD: DURING A RUNNING PROCESS, QUIT IT
{
	(void)sig;

	rl_on_new_line();
	rl_redisplay();
}

void		hand_eof(void)
{
	exit(0);
}

void	set_signal_handler(void)
{
	signal(SIGINT, hand_sigint);
	signal(SIGQUIT, hand_sigquit);
}

// /* EOF */
// 		if (line == NULL)
// 			hand_eof();
