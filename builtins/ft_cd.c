#include "minishell.h"

/*
cd_error	-> minishell: cd: <path>: <reason>, LIKE BASH
cd_target	-> WHERE TO GO: THE ARGUMENT, OR $HOME WHEN THERE IS NONE
update_pwd	-> REFRESH PWD AND OLDPWD, OR pwd WOULD START LYING
ft_cd		-> CHANGE THE WORKING DIRECTORY
*/

static int	cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}

static char	*cd_target(char **argv, t_env *env)
{
	char	*target;

	if (argv[1])
		return (argv[1]);
	target = find_env(env, "HOME", 4);
	if (!target)
		err_cmd("cd", "HOME not set", 1);
	return (target);
}

static void	update_pwd(t_env *env, char *old)
{
	char	*new;

	new = getcwd(NULL, 0);
	if (old)
		set_env(env, "OLDPWD", old);
	if (new)
		set_env(env, "PWD", new);
	free(new);
}

int	ft_cd(char **argv, t_env *env)
{
	char	*target;
	char	*old;

	if (argv[1] && argv[2])
		return (err_cmd("cd", "too many arguments", 2));
	if (argv[1] && !*argv[1])
		return (0);
	target = cd_target(argv, env);
	if (!target)
		return (1);
	old = getcwd(NULL, 0);
	if (chdir(target) != 0)
		return (free(old), cd_error(target));
	update_pwd(env, old);
	free(old);
	return (0);
}
