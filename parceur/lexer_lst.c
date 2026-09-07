#include "lexeur.h"

/*
free_lexer		-> FREE THE LEXER LIST
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

int	add_node_lexer(t_lst_lexer **liste, t_token_type type, char *token)
{
	t_lst_lexer	*new;
	t_lst_lexer	*ptr;

	new = malloc(sizeof(t_lst_lexer));
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
