#ifndef PARCEUR_H 
# define PARCEUR_H

# include "lexeur.h"

typedef enum e_node_type
{
	N_RED,
	N_PIPE,
	N_CMD
}	t_node_type;

typedef struct s_lst_ast
{
	char				**tokens;
	char				*red_file;
	t_node_type			node_type;
	t_token_type		token_type;
	struct s_lst_ast	*right;
	struct s_lst_ast	*left;
}				t_lst_ast;

//parceur_free.c
void			free_tab(char **tab);
void			free_parceur(t_lst_ast *head);

//parceur.c
t_lst_ast		*find_cmd(t_lst_lexer **head);
t_lst_ast		*find_red(t_lst_lexer **head);
t_lst_ast		*find_pipe(t_lst_lexer **head);

// print ast ----> A SUPPRIMER !!! 
void			print_ast(t_lst_ast *root);

#endif