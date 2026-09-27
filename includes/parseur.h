/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseur.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmoussa <anmoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 01:55:58 by anmoussa          #+#    #+#             */
/*   Updated: 2026/09/27 01:55:59 by anmoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSEUR_H
# define PARSEUR_H

# include "common.h"
# include "lexer.h"

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
	int					hd_quoted;
	int					hd_fd;
	t_node_type			node_type;
	t_token_type		token_type;
	struct s_lst_ast	*right;
	struct s_lst_ast	*left;
	struct s_lst_ast	*root;
}				t_lst_ast;

//parseur/parseur_cmd.c
t_lst_ast		*find_cmd(t_lst_lexer *head);

//parseur/parseur.c
t_lst_ast		*find_red(t_lst_lexer **head);
t_lst_ast		*find_pipe(t_lst_lexer **head);

//parseur/parseur_free.c
void			close_hd(t_lst_ast *node);
void			set_root(t_lst_ast *node, t_lst_ast *root);
void			free_parseur(t_lst_ast *head);

#endif
