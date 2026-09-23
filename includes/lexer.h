#ifndef LEXER_H
# define LEXER_H

# include "common.h"
# include "env.h"

# define BUF_MAX 4096

typedef enum e_token
{
	TOK_RED_BRS,//>>
	TOK_RED_BLS,//<<
	TOK_RED_BR, //>
	TOK_RED_BL, //<
	TOK_PIPE, //Pipes |
	TOK_OR, //|| , bonus operator, refused by check_syntax
	TOK_W, //Commands, op, env, $? and obj
	TOK_EOF,
}		t_token_type;

typedef struct s_lst_lexer
{
	t_token_type		type;
	char				*value;
	int					quoted;
	struct s_lst_lexer	*next;
}				t_lst_lexer;

//parseur/lexer.c
t_lst_lexer	*lexer(char *input, t_env *env);

//parseur/lexer_cut.c
char		*cut(char *raw_tok, t_env *env, int *initial_i, int *had_quote);

//parseur/lexer_op.c
void		add_red(char *input, int *i, t_lst_lexer **head);
void		add_pipe(char *input, int *i, t_lst_lexer **head);

//parseur/syntax.c
int			check_syntax(t_lst_lexer *head);

//parseur/lexer_lst.c
void		free_lexer(t_lst_lexer *head);
t_lst_lexer	*last_lexer(t_lst_lexer *head);
int			add_node_lexer(t_lst_lexer **liste, t_token_type type, char *token);

//parseur/istype.c
int			is_quotes_closed(char *input);
int			is_delim(char c);
int			ft_isspace(char c);

//parseur/expand.c
int			expand(char *raw, char *buffer, int *j, t_env *env);

#endif
