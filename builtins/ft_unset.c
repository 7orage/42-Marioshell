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
