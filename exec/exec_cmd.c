/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmoussa <anmoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 01:56:05 by anmoussa          #+#    #+#             */
/*   Updated: 2026/09/27 01:56:06 by anmoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
clean		-> FREE EVERYTHING, PRINT THE ERROR, GIVE BACK THE EXIT CODE
run_execve	-> REPLACE THE PROCESS BY THE COMMAND, NEVER COMES BACK.
		   SIGPIPE GOES BACK TO DEFAULT: AN IGNORED SIGNAL SURVIVES execve
exec_cmd	-> BUILTIN OR EXTERN COMMAND
*/

static int	clean(t_env *env, t_lst_ast *ast, char **argv, int n)
{
	free_list(env);
	if (n == 0)
		n = err_cmd(argv[0], "command not found", 127);
	else if (n == 1)
		n = err_sys("malloc");
	else if (n == 2)
		n = err_cmd(argv[0], "Is a directory", 126);
	else if (n == 3)
		n = err_cmd(argv[0], "Permission denied", 126);
	else if (n == 4)
		n = err_cmd(argv[0], strerror(errno), 127);
	free_parseur(ast->root);
	rl_clear_history();
	close_std();
	return (n);
}

static int	run_execve(char **argv, t_env *env, t_lst_ast *full_ast)
{
	char		**envp;
	char		*path;
	struct stat	s;

	path = find_path(argv[0], env);
	if (!path)
		exit(clean(env, full_ast, argv, 0));
	envp = env_to_tab(env);
	if (!envp)
		exit(clean(env, full_ast, argv, 1));
	signal(SIGPIPE, SIG_DFL);
	execve(path, argv, envp);
	free(path);
	free_tab(envp);
	if (stat(argv[0], &s) == 0 && S_ISDIR(s.st_mode))
		exit(clean(env, full_ast, argv, 2));
	if (errno == EACCES)
		exit(clean(env, full_ast, argv, 3));
	exit(clean(env, full_ast, argv, 4));
}

int	exec_cmd(t_lst_ast *cmd, t_env *env, t_lst_ast *full_ast)
{
	if (!cmd || !cmd->tokens || !cmd->tokens[0])
		return (0);
	if (is_builtin(cmd->tokens[0]))
		return (run_builtin(cmd->tokens, env, full_ast));
	return (run_execve(cmd->tokens, env, full_ast));
}
