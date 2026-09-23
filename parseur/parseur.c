#include "minishell.h"

/*
new_red		-> BUILD ONE N_RED NODE AND EAT ITS TARGET
find_red	-> STACK THE REDIRECTIONS, WALK THE WHOLE SIMPLE COMMAND
find_pipe	-> FIND A PIPE
*/

static t_lst_ast	*new_red(t_lst_lexer **head, t_lst_ast *left)
{
	t_lst_ast	*node;

	node = ft_calloc(1, sizeof(t_lst_ast));
	if (!node)
		return (NULL);
	node->node_type = N_RED;
	node->token_type = (*head)->type;
	node->left = left;
	node->hd_fd = -1;
	*head = (*head)->next;
	if (*head && (*head)->type == TOK_W)
	{
		node->red_file = ft_strdup((*head)->value);
		node->hd_quoted = (*head)->quoted;
		*head = (*head)->next;
	}
	return (node);
}

t_lst_ast	*find_red(t_lst_lexer **head)
{
	t_lst_ast	*node_left;
	t_lst_ast	*node_ast;

	node_left = find_cmd(*head);
	while (*head && (*head)->type != TOK_PIPE && (*head)->type != TOK_EOF)
	{
		if ((*head)->type == TOK_W)
		{
			*head = (*head)->next;
			continue ;
		}
		node_ast = new_red(head, node_left);
		if (!node_ast)
			return (free_parseur(node_left), NULL);
		node_left = node_ast;
	}
	return (node_left);
}

t_lst_ast	*find_pipe(t_lst_lexer **head)
{
	t_lst_ast	*node_left;
	t_lst_ast	*node_ast;

	node_left = find_red(head);
	if (!*head || (*head)->type != TOK_PIPE)
		return (node_left);
	node_ast = ft_calloc(1, sizeof(t_lst_ast));
	if (!node_ast)
		return (free_parseur(node_left), NULL);
	node_ast->node_type = N_PIPE;
	node_ast->token_type = (*head)->type;
	node_ast->hd_fd = -1;
	node_ast->left = node_left;
	*head = (*head)->next;
	node_ast->right = find_pipe(head);
	return (node_ast);
}
