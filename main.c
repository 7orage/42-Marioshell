#include "minishell.h"

/*
prompt_str	-> GREEN PROMPT AFTER A SUCCESS, RED AFTER A FAILURE
run_line	-> LEXER, AST, EXEC, THEN FREE EVERYTHING
shell_loop	-> MAIN LOOP OF THE SHELL
main		-> SET UP THE ENVIRONMENT AND START THE LOOP
*/

static char	*prompt_str(t_env *env)
{
	char	*code;

	code = find_env(env, "?", 1);
	if (code && ft_strncmp(code, "0", 2))
		return (PROMPT_KO);
	return (PROMPT_OK);
}

static void	run_line(char *line, t_env *env)
{
	t_lst_lexer	*head;
	t_lst_lexer	*ptr;
	t_lst_ast	*ast;
	int			status;

	head = lexer(line, env);
	if (!head)
		return (set_status(env, 2));
	ptr = head;
	ast = find_pipe(&ptr);
	free_lexer(head);
	if (!ast)
		return ;
	if (!collect_heredocs(ast, env))
	{
		g_signal = 0;
		free_parseur(ast);
		return (set_status(env, 130));
	}
	status = exec_ast(ast, env, 0);
	sig_msg(status);
	set_status(env, status);
	free_parseur(ast);
}

static void	shell_loop(t_env *env)
{
	char	*line;

	while (1)
	{
		sig_prompt();
		line = readline(prompt_str(env));
		if (g_signal == SIGINT)
			set_status(env, 130);
		g_signal = 0;
		if (!line)
		{
			ft_putendl_fd("exit", 2);
			return ;
		}
		if (*line)
		{
			add_history(line);
			run_line(line, env);
		}
		free(line);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;
	int		status;

	(void)argc;
	(void)argv;
	env = envp_list(envp);
	if (!env)
		return (1);
	shell_loop(env);
	status = ft_atoi(find_env(env, "?", 1));
	rl_clear_history();
	free_list(env);
	return (status);
}
