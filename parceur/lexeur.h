#ifndef LEXEUR_H
# define LEXEUR_H

# include "../includes/libft/libft.h"
# include "envp_list.h"

# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <errno.h>
# include <stdio.h>
# include <stdbool.h>
# include <string.h>

typedef enum
{
	TOK_RED_BRS,//>>
	TOK_RED_BLS,//<<
	TOK_RED_BR, //>
	TOK_RED_BL, //<
	TOK_PIPE, //Pipes |
	TOK_W, //Commands, op, env, $? and obj
	TOK_EOF,
}		token_type;

typedef struct	s_lst_lexer
{
	token_type			type;
	char				*value;
	struct s_lst_lexer	*next;
}				t_lst_lexer;

// lexer.c
t_lst_lexer	*lexer(char *input, t_env *env);

//lexer_cut.c
char		*cut(char *raw_tok, t_env *env, int *initial_i);

//lexer_lst.c
void		free_lexer(t_lst_lexer *head);
int			add_node_lexer(t_lst_lexer **liste, token_type type, char *token);

//istype.c
int	is_quotes_closed(char *input);
int			is_delim(char c);
int			ft_isspace(char c);

// expand.c
int		expand(char *raw, char *buffer, int *j, t_env *env);
char	*env_get(t_env *env, char *name, int len);
# endif