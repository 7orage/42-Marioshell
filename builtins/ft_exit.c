#include "minishell.h"

/*
is_number	-> [+-]?[0-9]+ AND NOTHING ELSE
exit_error	-> minishell: exit: abc: numeric argument required
ft_exit		-> LEAVE THE SHELL
*/

static int	is_number(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static void	exit_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": numeric argument required", 2);
}

int	ft_exit(char **argv, t_env *env)
{
	int	code;

	code = 0;
	ft_putendl_fd("exit", 2);
	if (!argv[1])
		code = ft_atoi(find_env(env, "?", 1));
	else if (!is_number(argv[1]))
	{
		exit_error(argv[1]);
		code = 2;
	}
	else if (argv[2])
		return (err_cmd("exit", "too many arguments", 1));
	else
		code = ft_atoi(argv[1]);
	free_list(env);
	rl_clear_history();
	exit(code & 255);
}
