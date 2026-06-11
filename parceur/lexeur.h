#ifndef LEXEUR_H
# define LEXEUR_H

// #include "minishell.h"
#include"../includes/libft/libft.h"
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>
#include <stdio.h>
# include<stdbool.h>
#include<string.h>

/*  

    POUR EXPAND: déclarer une variable globale "environ" (type: char **)

*/

typedef enum
{
    TOK_RED_BRS,//>>
    TOK_RED_BLS,//<<
    TOK_RED_BR, //>
    TOK_RED_BL, //<
    TOK_PIPE,   //Pipes |
    TOK_W,      //Commands, op, env, $? and obj
    TOK_EOF,
}               token_type;


typedef struct s_lst_lexer
{
    token_type       type;
    char                *value;
    struct s_lst_lexer    *next;
}               lst_lexer;

// lexer
void	free_lexer(lst_lexer *head);
int     add_node_lexer(lst_lexer **liste, token_type type, char *token);
char    *cut(char *raw_tok);
lst_lexer    *lexeur(char *input);

// istype
int     ft_isspace(char c);
int     is_red(char *token);
int     is_pipe(char *token);
int     is_exst(char *token);
int     is_venv(char *token);
int     is_cmd(char *token);
int     is_obj(char *token);
int     is_op(char *token);

# endif