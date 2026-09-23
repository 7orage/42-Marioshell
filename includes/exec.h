#ifndef EXEC_H
# define EXEC_H

# include "common.h"
# include "parseur.h"

# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

# define HD_TMP "/tmp/.minishell_heredoc"

//exec/exec.c
int			exec_ast(t_lst_ast *ast, t_env *env, int forked);
int			run_in_place(t_lst_ast *node, t_env *env);

//exec/heredoc.c
int			collect_heredocs(t_lst_ast *ast, t_env *env);

//exec/exec_cmd.c
int			exec_cmd(t_lst_ast *cmd, t_env *env);

//exec/exec_red.c
t_lst_ast	*deepest_cmd(t_lst_ast *node);
int			apply_reds(t_lst_ast *node);
int			run_saved(t_lst_ast *node, t_env *env);

//exec/exec_path.c
char		*find_path(char *cmd, t_env *env);
char		**env_to_tab(t_env *env);

//exec/exec_utils.c
int			wait_status(pid_t pid);
void		set_status(t_env *env, int code);

#endif
