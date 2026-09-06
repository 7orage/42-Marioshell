#include "lexeur.h"

/*
add_red		-> ADD A NODE WITH TOK_RED_XX TYPE
tokenize	-> WALK THE INPUT, ONE TOK A THE TIME
lexer		-> MANAGE THE CREATION OF THE LST
*/

static void	add_red(char *input, int *i, t_lst_lexer **head)
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

static int	tokenize(char *input, t_lst_lexer **head, t_env *env)
{
	char	*word;
	int		i;

	i = 0;
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '>' || input[i] == '<')
			add_red(input, &i, head);
		else if (input[i] == '|')
		{
			add_node_lexer(head, TOK_PIPE, NULL);
			i += 1;
		}
		else if (input[i])
		{
			word = cut(&input[i], env, &i);
			if (!word)
				return (0);
			add_node_lexer(head, TOK_W, word);
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
	return (head);
}
