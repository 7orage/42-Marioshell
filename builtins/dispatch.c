#include "minishell.h"

/*
is_builtin	-> 1 IF THE COMMAND IS A BUILTIN
run_builtin	-> SWITCH TO THE RIGHT BUILTIN, RETURNS ITS EXIT CODE
*/

int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strncmp(cmd, "echo", 5) || !ft_strncmp(cmd, "cd", 3))
		return (1);
	if (!ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "export", 7))
		return (1);
	if (!ft_strncmp(cmd, "unset", 6) || !ft_strncmp(cmd, "env", 4))
		return (1);
	return (!ft_strncmp(cmd, "exit", 5));
}

int	run_builtin(char **argv, t_env *env)
{
	if (!ft_strncmp(argv[0], "echo", 5))
		return (ft_echo(argv));
	if (!ft_strncmp(argv[0], "pwd", 4))
		return (ft_pwd());
	if (!ft_strncmp(argv[0], "env", 4))
		return (ft_env(env));
	if (!ft_strncmp(argv[0], "cd", 3))
		return (ft_cd(argv, env));
	if (!ft_strncmp(argv[0], "export", 7))
		return (ft_export(argv, env));
	if (!ft_strncmp(argv[0], "unset", 6))
		return (ft_unset(argv, env));
	return (ft_exit(argv, env));
}
