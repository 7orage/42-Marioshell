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

// FREE THE LIST

void	free_lexer(lst_lexer *head)
{
	lst_lexer	*ptr;

	while (head)
	{
		ptr = head->next;
		if (head->value)
			free(head->value);
		free(head);
		head = ptr;
	}
}

// ADD A NEW TOKEN TO THE LISTE
int	add_node_lexer(lst_lexer **liste, token_type type, char *token)
{
	lst_lexer	*new;
	lst_lexer	*ptr;

	new = malloc(sizeof(lst_lexer));
	if (!new)
		return (free(new), 0);
	new->type = type;
	if (token)
		new->value = token;
	else
		new->value = NULL;
	new->next = NULL;
	if (!*liste)
		*liste = new;
	else
	{
		ptr = *liste;
		while (ptr->next != NULL)
			ptr = ptr->next;
		ptr->next = new;
	}
	if (!new->value)
		return (1);
	else
		return (ft_strlen(new->value));
}

// CUT THE TOKEN PROPERLY
char    *cut(char *raw_tok, t_env *env, int *initial_i)
{
	char buffer[4096];
	int i = 0;
	int j = 0;
	int is_single = 0;
	int is_double = 0;

	while (raw_tok[i] && !(!is_single && !is_double
		&& (ft_isspace(raw_tok[i]) || is_delim(raw_tok[i]))))
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

lst_lexer    *lexeur(char *input, t_env *env)
{

	int			i = 0;
	lst_lexer	*head = NULL;

	if (!check_quotes(input))
	{
		ft_putstr_fd("minishell: syntax error: unclosed quote\n", 2);
		return (NULL);
	}
	while (input[i])
	{
		while (ft_isspace(input[i]))
			i++;
		if (input[i] == '>')
		{
			if (input[i + 1] == '>')
			{
				add_node_lexer(&head, TOK_RED_BRS, NULL);
				i += 1;
			}
			else
				add_node_lexer(&head, TOK_RED_BR, NULL);
			i += 1;
		}
		else if (input[i] == '<')
		{
			if (input[i + 1] == '<')
			{
				add_node_lexer(&head, TOK_RED_BLS, NULL);
				i += 1;
			}
			else
				add_node_lexer(&head, TOK_RED_BL, NULL);
			i += 1;
		}
		else if (input[i] == '|')
		{
			add_node_lexer(&head, TOK_PIPE, NULL);
			i += 1;
		}
		else if (input[i])
		{
			char *word = cut(&input[i], env, &i);
			if (!word)
				return (free_lexer(head), NULL);
			add_node_lexer(&head, TOK_W, word);
		}
	}
	add_node_lexer(&head, TOK_EOF, NULL);
	return (head);
}
