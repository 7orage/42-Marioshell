#include "minishell.h"

/*
child_pipe	-> PLUG THE CHILD ON THE PIPE THEN RESTART THE RECURSION
exec_pipe	-> ONE PIPE, TWO FORKS, ONE PER BRANCH
run_in_place	-> REDIRECTIONS THEN COMMAND, IN THE CURRENT PROCESS
exec_branch	-> WHO FORKS: BUILTIN IN THE SHELL, EXTERN IN A CHILD
exec_ast	-> RECURSIVE SWITCH ON THE AST
*/

static void	child_pipe(t_lst_ast *node, t_env *env, int *fd, int side)
{
	sig_child();
	if (side == 1)
		dup2(fd[1], STDOUT_FILENO);
	else
		dup2(fd[0], STDIN_FILENO);
	close(fd[0]);
	close(fd[1]);
	exit(exec_ast(node, env, 1));
}

static int	exec_pipe(t_lst_ast *ast, t_env *env)
{
	int	fd[2];
	int	pid[2];

	if (pipe(fd) == -1)
		return (err_sys("pipe"));
	sig_exec();
	pid[0] = fork();
	if (pid[0] == 0)
		child_pipe(ast->left, env, fd, 1);
	pid[1] = fork();
	if (pid[1] == 0)
		child_pipe(ast->right, env, fd, 0);
	close(fd[0]);
	close(fd[1]);
	if (pid[0] < 0 || pid[1] < 0)
		return (err_sys("fork"));
	wait_status(pid[0]);
	return (wait_status(pid[1]));
}

int	run_in_place(t_lst_ast *node, t_env *env)
{
	if (!apply_reds(node))
		return (1);
	return (exec_cmd(deepest_cmd(node), env));
}

static int	exec_branch(t_lst_ast *node, t_env *env, int forked)
{
	t_lst_ast	*cmd;
	pid_t		pid;

	if (forked)
		return (run_in_place(node, env));
	cmd = deepest_cmd(node);
	if (cmd && cmd->tokens && is_builtin(cmd->tokens[0]))
		return (run_saved(node, env));
	sig_exec();
	pid = fork();
	if (pid < 0)
		return (err_sys("fork"));
	if (pid == 0)
	{
		sig_child();
		exit(run_in_place(node, env));
	}
	return (wait_status(pid));
}

int	exec_ast(t_lst_ast *ast, t_env *env, int forked)
{
	if (!ast)
		return (0);
	if (ast->node_type == N_PIPE)
		return (exec_pipe(ast, env));
	return (exec_branch(ast, env, forked));
}
