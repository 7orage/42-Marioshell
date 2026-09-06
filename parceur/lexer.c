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


// CUT THE TOKEN PROPERLY
char    *cut(char *raw_tok, t_env *env, int *initial_i)
{
	char buffer[4096];
	int i = 0;
	int j = 0;
	int is_single = 0;
	int is_double = 0;

	while (raw_tok[i] && !(!is_single && !is_double && (ft_isspace(raw_tok[i]) || is_delim(raw_tok[i]))))
	{
		if (!is_single && !is_double && raw_tok[i] == '\'') // tout premier '
		{
			is_single = 1;
			i++;
		}
		else if (!is_double && !is_single && raw_tok[i] == '"') // tout premier "
		{
			is_double = 1;
			i++;
		}
		else if (is_single)
		{
			if (raw_tok[i] == '\'')
			{
				is_single = 0;
				i++;
			}
			else
			{
				buffer[j] = raw_tok[i];
				i++;
				j++;
			}
		}
		else if (is_double)
		{
			if (raw_tok[i] == '$')
			{
				i += expand(&raw_tok[i], buffer, &j, env);
			}
			else if (raw_tok[i] == '"')
			{
				is_double = 0;
				i++;
			}
			else
			{
				buffer[j] = raw_tok[i];
				i++;
				j++;
			}
		}
		else
		{
			if (raw_tok[i] == '$')
			{
				i += expand(&raw_tok[i], buffer, &j, env);
			}
			else
			{
				buffer[j] = raw_tok[i];
				i++;
				j++;
			}

		}
	}
	buffer[j] = '\0';
	*initial_i += i;
	return (ft_strdup(buffer));
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
