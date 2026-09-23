#include "minishell.h"

/*
count_words	-> COUNT THE WORDS OF THE WHOLE SIMPLE COMMAND
fill_tokens	-> COPY THEM
find_cmd	-> BUILD THE N_CMD NODE. DOES NOT MOVE head
*/

static int	count_words(t_lst_lexer *cur)
{
	int	i;

	i = 0;
	while (cur && cur->type != TOK_PIPE && cur->type != TOK_EOF)
	{
		if (cur->type == TOK_W)
		{
			i++;
			cur = cur->next;
		}
		else
		{
			cur = cur->next;
			if (cur && cur->type == TOK_W)
				cur = cur->next;
		}
	}
	return (i);
}

static char	**fill_tokens(t_lst_lexer *cur, int count)
{
	char	**tokens;
	int		j;

	tokens = ft_calloc(count + 1, sizeof(char *));
	if (!tokens)
		return (NULL);
	j = 0;
	while (j < count && cur)
	{
		if (cur->type == TOK_W)
		{
			tokens[j] = ft_strdup(cur->value);
			j++;
			cur = cur->next;
		}
		else
		{
			cur = cur->next;
			if (cur && cur->type == TOK_W)
				cur = cur->next;
		}
	}
	return (tokens);
}

t_lst_ast	*find_cmd(t_lst_lexer *head)
{
	t_lst_ast	*node_ast;
	int			count;

	node_ast = ft_calloc(1, sizeof(t_lst_ast));
	if (!node_ast)
		return (NULL);
	node_ast->node_type = N_CMD;
	node_ast->token_type = TOK_W;
	node_ast->hd_fd = -1;
	count = count_words(head);
	node_ast->tokens = fill_tokens(head, count);
	return (node_ast);
}
