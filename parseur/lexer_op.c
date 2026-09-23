#include "minishell.h"

/*
add_red		-> ADD A NODE WITH TOK_RED_XX TYPE
add_pipe	-> ADD A TOK_PIPE, OR A TOK_OR WHEN THE TWO | ARE GLUED
*/

void	add_red(char *input, int *i, t_lst_lexer **head)
{
	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			add_node_lexer(head, TOK_RED_BRS, NULL);
			*i += 1;
		}
		else
			add_node_lexer(head, TOK_RED_BR, NULL);
		*i += 1;
	}
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			add_node_lexer(head, TOK_RED_BLS, NULL);
			*i += 1;
		}
		else
			add_node_lexer(head, TOK_RED_BL, NULL);
		*i += 1;
	}
}

void	add_pipe(char *input, int *i, t_lst_lexer **head)
{
	if (input[*i + 1] == '|')
	{
		add_node_lexer(head, TOK_OR, NULL);
		*i += 1;
	}
	else
		add_node_lexer(head, TOK_PIPE, NULL);
	*i += 1;
}
