/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmoussa <anmoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 01:55:56 by anmoussa          #+#    #+#             */
/*   Updated: 2026/09/27 01:55:57 by anmoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "common.h"
# include "utils.h"

/* THE SHELL INTERFACE */
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>

/* THE MODULES */
# include "env.h"
# include "lexer.h"
# include "parseur.h"
# include "signals.h"
# include "builtins.h"
# include "exec.h"


# define PROMPT_OK "\001\033[0;32m\002◉ marioshell$ \001\033[0m\002"
# define PROMPT_KO "\001\033[0;31m\002◉ marioshell$ \001\033[0m\002"


#endif
