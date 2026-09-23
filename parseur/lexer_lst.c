#include "minishell.h"

/*
free_lexer		-> FREE THE LEXER LIST
last_lexer		-> LAST NODE OF THE LIST, NULL IF THE LIST IS EMPTY
add_node_lexer	-> ADD NEW NODE IN THE LIST
*/

void	free_lexer(t_lst_lexer *head)
{
	t_lst_lexer	*ptr;

	while (head)
	{
		ptr = head->next;
		if (head->value)
			free(head->value);
		free(head);
		head = ptr;
	}
}

t_lst_lexer	*last_lexer(t_lst_lexer *head)
{
	while (head && head->next)
		head = head->next;
	return (head);
}

int	add_node_lexer(t_lst_lexer **liste, t_token_type type, char *token)
{
	t_lst_lexer	*new;
	t_lst_lexer	*ptr;

	new = ft_calloc(1, sizeof(t_lst_lexer));
	if (!new)
		return (0);
	new->type = type;
	new->value = token;
	ptr = last_lexer(*liste);
	if (!ptr)
		*liste = new;
	else
		ptr->next = new;
	if (!new->value)
		return (1);
	return (ft_strlen(new->value));
}
