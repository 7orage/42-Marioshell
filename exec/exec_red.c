#include "minishell.h"

/*
deepest_cmd	-> GO DOWN THE RED CHAIN UNTIL THE COMMAND
open_red	-> OPEN A FILE AND PLUG IT ON 0 OR 1
apply_reds	-> APPLY FROM THE DEEPEST RED TO THE HIGHEST ONE
run_saved	-> SAVE 0 AND 1, RUN IN THE SHELL, PUT THEM BACK
*/

t_lst_ast	*deepest_cmd(t_lst_ast *node)
{
	while (node && node->node_type == N_RED)
		node = node->left;
	return (node);
}

static int	open_red(t_lst_ast *node)
{
	int	fd;

	if (!node->red_file)
		return (0);
	if (node->token_type == TOK_RED_BLS)
		fd = node->hd_fd;
	else if (node->token_type == TOK_RED_BR)
		fd = open(node->red_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->token_type == TOK_RED_BRS)
		fd = open(node->red_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(node->red_file, O_RDONLY);
	if (fd < 0)
		return (err_file(node->red_file));
	if (node->token_type == TOK_RED_BL || node->token_type == TOK_RED_BLS)
		dup2(fd, STDIN_FILENO);
	else
		dup2(fd, STDOUT_FILENO);
	return (close(fd), 1);
}

int	apply_reds(t_lst_ast *node)
{
	if (!node || node->node_type != N_RED)
		return (1);
	if (!apply_reds(node->left))
		return (0);
	return (open_red(node));
}

int	run_saved(t_lst_ast *node, t_env *env)
{
	int	save[2];
	int	status;

	save[0] = dup(STDIN_FILENO);
	save[1] = dup(STDOUT_FILENO);
	if (save[0] < 0 || save[1] < 0)
		return (err_sys("dup"));
	status = run_in_place(node, env);
	dup2(save[0], STDIN_FILENO);
	dup2(save[1], STDOUT_FILENO);
	close(save[0]);
	close(save[1]);
	return (status);
}
