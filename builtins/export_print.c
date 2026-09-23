#include "minishell.h"

/*
name_cmp	-> LEXICOGRAPHIC COMPARISON OF TWO VARIABLE NAMES
next_name	-> THE SMALLEST NAME STILL GREATER THAN prev
export_print	-> "export" WITH NO ARGUMENT: THE SORTED declare -x LIST
*/

static int	name_cmp(char *a, char *b)
{
	size_t	n;

	n = ft_strlen(a);
	if (ft_strlen(b) > n)
		n = ft_strlen(b);
	return (ft_strncmp(a, b, n + 1));
}

static char	*next_name(t_env *env, char *prev)
{
	char	*best;

	best = NULL;
	while (env)
	{
		if (is_identifier(env->name)
			&& (!prev || name_cmp(env->name, prev) > 0)
			&& (!best || name_cmp(env->name, best) < 0))
			best = env->name;
		env = env->next;
	}
	return (best);
}

void	export_print(t_env *env)
{
	char	*name;
	char	*value;

	name = next_name(env, NULL);
	while (name)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(name, 1);
		value = find_env(env, name, ft_strlen(name));
		if (value)
		{
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(value, 1);
			ft_putstr_fd("\"", 1);
		}
		ft_putstr_fd("\n", 1);
		name = next_name(env, name);
	}
}
