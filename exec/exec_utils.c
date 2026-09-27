/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmoussa <anmoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 01:56:12 by anmoussa          #+#    #+#             */
/*   Updated: 2026/09/27 01:56:13 by anmoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
wait_status	-> WAIT FOR A CHILD AND TRANSLATE ITS EXIT CODE
set_status	-> WRITE THE EXIT CODE IN THE HIDDEN "?" VARIABLE
child_exit	-> THE ONLY WAY OUT OF A CHILD: FREE EVERYTHING, THEN EXIT
*/

int	wait_status(pid_t pid)
{
	int	status;

	status = 0;
	if (waitpid(pid, &status, 0) < 0)
		return (1);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (1);
}

void	set_status(t_env *env, int code)
{
	char	*value;

	value = ft_itoa(code);
	if (!value)
		return ;
	while (env)
	{
		if (env->name && env->name[0] == '?' && env->name[1] == '\0')
		{
			free(env->content);
			env->content = value;
			return ;
		}
		env = env->next;
	}
	free(value);
}

void	child_exit(t_lst_ast *node, t_env *env, int status)
{
	free_list(env);
	if (node)
		free_parseur(node->root);
	rl_clear_history();
	close_std();
	exit(status);
}
