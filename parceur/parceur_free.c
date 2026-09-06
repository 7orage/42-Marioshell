#include "parceur.h"

/*
free_tab		-> FREE TAB
free_parceur	-> FREE AST
*/

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		if (tab[i] != NULL)
			free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_parceur(t_lst_ast *head)
{
	if (!head)
		return ;
	if (head->left)
		free_parceur(head->left);
	if (head->right)
		free_parceur(head->right);
	if (head->tokens)
		free_tab(head->tokens);
	if (head->red_file)
		free(head->red_file);
	free(head);
}
