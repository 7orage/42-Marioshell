/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmoussa <anmoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 01:55:33 by anmoussa          #+#    #+#             */
/*   Updated: 2026/09/27 01:55:34 by anmoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
close_hd	-> CLOSE EVERY HEREDOC FD OF A SUBTREE
set_root	-> TELL EVERY NODE WHERE ITS TREE STARTS, SO A CHILD CAN FREE IT ALL
free_parseur	-> FREE THE AST
*/

void	close_hd(t_lst_ast *node)
{
	if (!node)
		return ;
	if (node->hd_fd > 0)
	{
		close(node->hd_fd);
		node->hd_fd = -1;
	}
	close_hd(node->left);
	close_hd(node->right);
}

void	set_root(t_lst_ast *node, t_lst_ast *root)
{
	if (!node)
		return ;
	node->root = root;
	set_root(node->left, root);
	set_root(node->right, root);
}

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
