#ifndef PARCEUR_H 
# define PARCEUR_H

#include"lexeur.h"


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
typedef enum
{
    N_RED,     //Redirections
    N_PIPE,   //Pipe |
    N_PAR,    //Parenthesis
    N_CMD,      //Commands, op, env, $? and obj
    N_EOF
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

// print
void    print_ast(lst_ast *root);

#endif