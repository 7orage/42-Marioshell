#include "minishell.h"

/*
is_hd_delim	-> IS THE WORD WE ARE ABOUT TO CUT A HEREDOC DELIMITER ?
add_word	-> CUT ONE WORD AND PUSH IT, NO EXPAND AFTER A <<
tokenize	-> WALK THE INPUT, ONE TOKEN AT A TIME
lexer		-> MANAGE THE CREATION OF THE LST
*/

static int	is_hd_delim(t_lst_lexer *head)
{
	head = last_lexer(head);
	if (head && head->type == TOK_RED_BLS)
		return (1);
	return (0);
}

static int	add_word(char *input, int *i, t_lst_lexer **head, t_env *env)
{
	t_lst_lexer	*tail;
	char		*word;
	int			quoted;

	quoted = 0;
	if (is_hd_delim(*head))
		env = NULL;
	word = cut(&input[*i], env, i, &quoted);
	if (!word)
		return (0);
	if (!*word && !quoted)
		return (free(word), 1);
	add_node_lexer(head, TOK_W, word);
	tail = last_lexer(*head);
	if (tail)
		tail->quoted = quoted;
	return (1);
}

static int	tokenize(char *input, t_lst_lexer **head, t_env *env)
{
	int	i;

	i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '>' || input[i] == '<')
			add_red(input, &i, head);
		else if (input[i] == '|')
			add_pipe(input, &i, head);
		else if (input[i])
		{
			if (!add_word(input, &i, head, env))
				return (0);
		}
	}
	return (1);
}

t_lst_lexer	*lexer(char *input, t_env *env)
{
	t_lst_lexer	*head;

	head = NULL;
	if (!is_quotes_closed(input))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		return (NULL);
	}
	if (!tokenize(input, &head, env))
		return (free_lexer(head), NULL);
	add_node_lexer(&head, TOK_EOF, NULL);
	if (!check_syntax(head))
		return (free_lexer(head), NULL);
	return (head);
}
