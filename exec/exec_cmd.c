#include "minishell.h"

/*
run_execve	-> REPLACE THE PROCESS BY THE COMMAND, NEVER COMES BACK
exec_cmd	-> BUILTIN OR EXTERN COMMAND
*/

static int	run_execve(char **argv, t_env *env)
{
	char	**envp;
	char	*path;

	path = find_path(argv[0], env);
	if (!path)
		exit(err_cmd(argv[0], "command not found", 127));
	envp = env_to_tab(env);
	if (!envp)
		exit(err_sys("malloc"));
	execve(path, argv, envp);
	free(path);
	free_tab(envp);
	if (errno == EACCES || errno == EISDIR)
		exit(err_cmd(argv[0], strerror(errno), 126));
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
