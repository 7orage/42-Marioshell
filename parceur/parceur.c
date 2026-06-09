#include "parceur.h"

/* PRIORITES

	() > Red > Pipe

	donc pour une ligne: "echo hello | cat > file.txt", on a 
	[TOK_W:"echo"] [TOK_W:"hello"] [TOK_PIPE] [TOK_W:"cat"] [TOK_RED_BR] [TOK_W:"file.txt"] [TOK_EOF]

				Pipe
		echo			Red
		hello 	// cat		file.txt

		--> On parcour la ligne: de gauche à droite 
		!! CHANGER PROTO LST_LEXER, AJOUTER NOEUD PRECEDENT
		!! AJOUTER MESSAGES ERREURS 
		!! DIFFERENCIER CMD DE NOM FICHIER ECT

		-> si on arrive sur ()  alors backtracking, on renvoit à l'algo principal, pour refaire meme procede
		-> si on arrive sur |   alors on cree nv noeud parent de l'AST et ajout ce qu'il y a à gauche/droite
		-> si on arrive sur red alors de meme creer nv noeud parent de l'AST et inclure droite/gauche 

*/

lst_ast	*find_cmd(lst_lexer **head)
{
	lst_lexer		*current = *head;
	lst_ast	*node_ast = ft_calloc(sizeof(lst_ast), 1);
	char	**tokens;
	int		i = 0;
	int		j = 0;

	node_ast->node_type = N_CMD;
	node_ast->token_type = TOK_W;
	node_ast->right = NULL;
	node_ast->left = NULL;
	while (current->type == TOK_W)
	{
		i++;
		current = current->next;
	}
	tokens = ft_calloc(i + 1, sizeof(char *));
	current = *head;
	while(i > 0)
	{
		tokens[j] = ft_strdup(current->value);
		current = current->next;
		j++;
		i--;
	}
	node_ast->tokens = tokens;
	*head = current;
	return (node_ast);
}

lst_ast	*find_red(lst_lexer **head)
{
	lst_ast	*node_left;
	lst_ast	*node_ast = ft_calloc(sizeof(lst_ast), 1);

	node_left = find_cmd(head);
	if ((*head)->type == TOK_RED_BR || (*head)->type == TOK_RED_BL || (*head)->type == TOK_RED_BRS || (*head)->type == TOK_RED_BLS)
	{
		node_ast->token_type = (*head)->type;
		(*head) = (*head)->next;
		node_ast->red_file = ft_strdup((*head)->value);
		node_ast->node_type = N_RED;
		node_ast->left = node_left;
		(*head) = (*head)->next;
	}
	else
		return (node_left); // free_node_ast(node_ast), 
	return (node_ast);
}

lst_ast	*find_pipe(lst_lexer **head)
{
	lst_ast	*node_left;
	lst_ast	* const node_ast = ft_calloc(sizeof(lst_ast), 1);

	node_left = find_red(head);
	if ((*head)->type == TOK_PIPE)
	{
		node_ast->token_type = (*head)->type;
		node_ast->node_type = N_PIPE;
		node_ast->left = node_left;
		(*head) = (*head)->next;
		node_ast->right = find_pipe(head);
	}
	else
		return (node_left); // free_node_ast(node_ast), 
	return (node_ast);
}

lst_ast	*create_ast(lst_lexer **liste)
{
	lst_ast	*head = find_pipe(liste);
	return (head);
}
