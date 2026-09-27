/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmoussa <anmoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 01:55:49 by anmoussa          #+#    #+#             */
/*   Updated: 2026/09/27 01:55:50 by anmoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "common.h"

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

//parseur/envp_list.c
t_env	*envp_list(char **envp);
void	free_list(t_env *env);

//parseur/expand.c
char	*find_env(t_env *env, char *name, int len);

#endif
