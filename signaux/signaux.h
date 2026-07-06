#ifndef SIG_H
# define SIG_H

// #include "minishell.h"
# include <signal.h>
# include <sys/types.h>

#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <unistd.h>


void	set_signal_handler(void);
void	hand_eof(void);

# endif