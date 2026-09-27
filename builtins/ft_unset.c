/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmoussa <anmoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 01:56:40 by anmoussa          #+#    #+#             */
/*   Updated: 2026/09/27 01:56:41 by anmoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
ft_unset	-> REMOVE VARIABLES, SILENT ON A NAME THAT DOES NOT EXIST
*/

int	ft_unset(char **argv, t_env *env)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (is_identifier(argv[i]))
			del_env(env, argv[i]);
		i++;
	}
	return (0);
}
