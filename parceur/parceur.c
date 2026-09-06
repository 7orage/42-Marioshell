#include "parceur.h"

/*
count_words	-> [find_cmd] COUNNT THE WORDS
fill_tokens	-> [find_cmd] COPY THEM
find_cmd	-> FIND A COMAND
find_red	-> FIND A REDIRECTION
find_pipe	-> FIND A PIPE
*/

static int	count_words(t_lst_lexer *current)
{
	int	i;

	i = 0;
	while (current && current->type == TOK_W)
	{
		i++;
		current = current->next;
	}
	return (i);
}

static char	**fill_tokens(t_lst_lexer **head, int count)
{
	char	**tokens;
	int		j;

	tokens = ft_calloc(count + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	j = 0;
	while (j < count)
	{
		tokens[j] = ft_strdup((*head)->value);
		*head = (*head)->next;
		j++;
	}
	return (tokens);
}

t_lst_ast	*find_cmd(t_lst_lexer **head)
{
	t_lst_ast	*node_ast;
	int			count;

	node_ast = ft_calloc(1, sizeof(t_lst_ast));
	if (!node_ast)
		return (NULL);
	node_ast->node_type = N_CMD;
	node_ast->token_type = TOK_W;
	count = count_words(*head);
	node_ast->tokens = fill_tokens(head, count);
	return (node_ast);
}

t_lst_ast	*find_red(t_lst_lexer **head)
{
	t_lst_ast	*node_left;
	t_lst_ast	*node_ast;

	node_left = find_cmd(head);
	if ((*head)->type == TOK_RED_BR || (*head)->type == TOK_RED_BL
		|| (*head)->type == TOK_RED_BRS || (*head)->type == TOK_RED_BLS)
	{
		node_ast = ft_calloc(sizeof(t_lst_ast), 1);
		if (!node_ast)
			return (free_parceur(node_left), NULL);
		node_ast->node_type = N_RED;
		node_ast->token_type = (*head)->type;
		node_ast->left = node_left;
		(*head) = (*head)->next;
		if (*head && (*head)->type == TOK_W)
		{
			node_ast->red_file = ft_strdup((*head)->value);
			(*head) = (*head)->next;
		}
		return (node_ast);
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
		return (free_parceur(node_left), NULL);
	node_ast->node_type = N_PIPE;
	node_ast->token_type = (*head)->type;
	node_ast->left = node_left;
	*head = (*head)->next;
	node_ast->right = find_pipe(head);
	return (node_ast);
}
