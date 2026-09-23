#ifndef MINISHELL_H
# define MINISHELL_H

# include "common.h"
# include "utils.h"

/* THE SHELL INTERFACE */
# include <readline/history.h>
# include <readline/readline.h>

/* THE MODULES */
# include "env.h"
# include "lexer.h"
# include "parseur.h"
# include "signals.h"
# include "builtins.h"
# include "exec.h"

/*
The prompt says how the last command went: green on 0, red otherwise.
The \001 and \002 markers tell readline "what is between these is
invisible", so it still counts the real width of the line when editing.
*/
# define PROMPT_OK "\001\033[0;32m\002◉ marioshell$ \001\033[0m\002"
# define PROMPT_KO "\001\033[0;31m\002◉ marioshell$ \001\033[0m\002"

#endif
