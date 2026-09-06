#include"lexeur.h"

int	check_quotes(char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (!quote && (input[i] == '\'' || input[i] == '"'))
			quote = input[i];
		else if (quote && input[i] == quote)
			quote = 0;
		i++;
	}
	if (quote)
		return (0);
	return (1);
}

void	check_red(char *input, int *i, lst_lexer **head)
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

lst_lexer    *lexeur(char *input, t_env *env)
{

	int			i = 0;
	lst_lexer	*head = NULL;
	char *word;

	if (!check_quotes(input))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		return (NULL);
	}
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '>' || input[i] == '<')
			check_red(input, &i, &head);
		else if (input[i] == '|')
		{
			add_node_lexer(&head, TOK_PIPE, NULL);
			i += 1;
		}
		else if (input[i])
		{
			word = cut(&input[i], env, &i);
			if (!word)
				return (free_lexer(head), NULL);
			add_node_lexer(&head, TOK_W, word);
		}
	}
	add_node_lexer(&head, TOK_EOF, NULL);
	return (head);
}
