#include "minishell.h"

/*
ft_env	-> PRINT EVERY EXPORTED VARIABLE
*/

int	ft_env(t_env *env)
{
	while (env)
	{
		if (is_identifier(env->name) && env->content)
		{
			ft_putstr_fd(env->name, 1);
			ft_putstr_fd("=", 1);
			ft_putendl_fd(env->content, 1);
		}
		env = env->next;
	}
	return (0);
}
