#ifndef PARCEUR_H 
# define PARCEUR_H

#include"lexeur.h"
#include"envp_list.h"


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

		-> si on arrive sur |   alors on cree nv noeud parent de l'AST et ajout ce qu'il y a à gauche/droite
		-> si on arrive sur red alors de meme creer nv noeud parent de l'AST et inclure droite/gauche 

		ABANDON NOEUD EOF AST
*/
typedef enum
{
    N_RED,     //Redirections
    N_PIPE,   //Pipe |
    N_CMD      //Commands, op, env, $? and obj
}               node_type;

typedef struct s_lst_ast
{
    char            **tokens;
    char            *red_file;
    node_type       node_type;
    token_type      token_type;
    struct s_lst_ast    *right;
    struct s_lst_ast    *left;
}              lst_ast;

// parceur
void	free_tab(char **tab);
void	free_parceur(lst_ast *head);
lst_ast	*find_cmd(lst_lexer **head);
lst_ast	*find_red(lst_lexer **head);
lst_ast	*find_pipe(lst_lexer **head);
lst_ast	*create_ast(lst_lexer **liste);



// print ast
void    print_ast(lst_ast *root);


#endif