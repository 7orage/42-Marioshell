#ifndef SIGNALS_H
# define SIGNALS_H

# include "common.h"

/* FOR sig_atomic_t, sigaction, SIGINT, SIGQUIT */
# include <signal.h>

extern volatile sig_atomic_t	g_signal;

//signals/sig_heredoc.c
void	sig_heredoc(void);

//signals/signals.c
void	sig_prompt(void);
void	sig_exec(void);
void	sig_child(void);
void	sig_msg(int status);

#endif
