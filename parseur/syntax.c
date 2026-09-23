#include "minishell.h"

/*
tok_str		-> THE TEXT BASH PRINTS FOR AN OPERATOR
syntax_error	-> THE ONLY PLACE THAT PRINTS "near unexpected token"
err_eof		-> WHAT BASH SAYS WHEN THE LINE STOPS ON A PIPE
check_pair	-> IS THIS OPERATOR FOLLOWED BY WHAT IT NEEDS ?
check_syntax	-> ONE PASS ON THE TOKENS, BEFORE THE PARSER SEES THEM
*/

static char	*tok_str(t_token_type type)
{
	if (type == TOK_RED_BRS)
		return (">>");
	if (type == TOK_RED_BLS)
		return ("<<");
	if (type == TOK_RED_BR)
		return (">");
	if (type == TOK_RED_BL)
		return ("<");
	if (type == TOK_OR)
		return ("||");
	if (type == TOK_PIPE)
		return ("|");
	return ("newline");
}

static int	syntax_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd(token, 2);
	ft_putstr_fd("'\n", 2);
	return (0);
}

static int	err_eof(void)
{
	ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
	return (0);
}

static int	check_pair(t_lst_lexer *cur, t_lst_lexer *prev)
{
	if (cur->type == TOK_W)
		return (1);
	if (cur->type == TOK_OR)
		return (syntax_error(tok_str(cur->type)));
	if (cur->type == TOK_PIPE)
	{
		if (!prev || prev->type == TOK_PIPE)
			return (syntax_error(tok_str(cur->type)));
		if (!cur->next || cur->next->type == TOK_EOF)
			return (err_eof());
		return (1);
	}
	if (!cur->next || cur->next->type == TOK_EOF)
		return (syntax_error("newline"));
	if (cur->next->type != TOK_W)
		return (syntax_error(tok_str(cur->next->type)));
	return (1);
}

int	check_syntax(t_lst_lexer *head)
{
	t_lst_lexer	*prev;

	prev = NULL;
	while (head && head->type != TOK_EOF)
	{
		if (!check_pair(head, prev))
			return (0);
		prev = head;
		head = head->next;
	}
	return (1);
}
