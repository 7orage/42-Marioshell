#ifndef PARCEUR_H
# define PARCEUR_H

// #include "minishell.h"
#include "../includes/libft/libft.h"
# include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <errno.h>

typedef enum
{
    TOK_RED = 0,    //Redirections
    TOK_PIPE = 0,   //Pipes
    TOK_HENV = 0,   //Handle env
    TOK_EXST = 0,   //Exit status ($?)
    TOK_CMD = 0,    //Commandes
    TOK_OP = 0,     //Options 
    TOK_OBJ = 0,    //NOm fichiers etc
    TOK_EOF = 0,
}               token_type;


typedef struct s_parceur
{
    token_type       type;
    char                *value;
    struct s_parceur    *next;
}               parceur;


int	add_node_parceur(token_type type, char *token, parceur **liste);
int     ft_isspace(char c);
int     is_red(char *token);
int     is_pipe(char *token);
int     is_exst(char *token);
int     is_venv(char *token);
int     is_cmd(char *token);
int     is_obj(char *token);

# endif