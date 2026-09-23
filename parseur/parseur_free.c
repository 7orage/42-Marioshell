#include "minishell.h"

/*
free_parseur	-> FREE THE AST
*/

void	free_parseur(t_lst_ast *head)
{
	if (!head)
		return ;
	if (head->left)
		free_parseur(head->left);
	if (head->right)
		free_parseur(head->right);
	if (head->tokens)
		free_tab(head->tokens);
	if (head->red_file)
		free(head->red_file);
	if (head->hd_fd > 0)
		close(head->hd_fd);
	free(head);
}
