#include "minishell.h"

/*
run_execve	-> REPLACE THE PROCESS BY THE COMMAND, NEVER COMES BACK
exec_cmd	-> BUILTIN OR EXTERN COMMAND
*/

static int	run_execve(char **argv, t_env *env)
{
	char		**envp;
	char		*path;
	struct stat	s;

	path = find_path(argv[0], env);
	if (!path)
		exit(err_cmd(argv[0], "command not found", 127));
	envp = env_to_tab(env);
	if (!envp)
		exit(err_sys("malloc"));
	execve(path, argv, envp);
	free(path);
	free_tab(envp);
	if (stat(argv[0], &s) == 0)
	{
		if (s.st_mode & __S_IFDIR)
			exit(err_cmd(argv[0], "Is a directory", 126));
	}
	if (errno == EACCES)
		exit(err_cmd(argv[0], "Permission denied", 126));
	exit(err_cmd(argv[0], strerror(errno), 127));
}

int	exec_cmd(t_lst_ast *cmd, t_env *env)
{
	if (!cmd || !cmd->tokens || !cmd->tokens[0])
		return (0);
	if (is_builtin(cmd->tokens[0]))
		return (run_builtin(cmd->tokens, env));
	return (run_execve(cmd->tokens, env));
}
