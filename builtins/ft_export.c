#include "minishell.h"

/*
bad_id		-> minishell: export: `2bad': not a valid identifier
export_one	-> HANDLE ONE ARGUMENT, RETURNS 1 ON ERROR
ft_export	-> DECLARE OR SET VARIABLES
*/

static int	bad_id(char *arg)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	return (1);
}

static int	export_one(char *arg, t_env *env)
{
	char	*name;
	char	*eq;
	int		ok;

	eq = ft_strchr(arg, '=');
	if (eq)
		name = ft_substr(arg, 0, eq - arg);
	else
		name = ft_strdup(arg);
	if (!name)
		return (1);
	if (!is_identifier(name))
		return (free(name), bad_id(arg));
	ok = 1;
	if (eq)
		ok = set_env(env, name, eq + 1);
	else if (!find_env(env, name, ft_strlen(name)))
		ok = set_env(env, name, NULL);
	free(name);
	return (!ok);
}

int	ft_export(char **argv, t_env *env)
{
	int	i;
	int	code;

	if (!argv[1])
	{
		export_print(env);
		return (0);
	}
	i = 1;
	code = 0;
	while (argv[i])
	{
		if (export_one(argv[i], env))
			code = 1;
		i++;
	}
	return (code);
}
