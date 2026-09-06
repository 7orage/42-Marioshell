#include "lexeur.h"

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
