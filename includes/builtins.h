#ifndef BUILTINS_H
# define BUILTINS_H

# include "common.h"
# include "env.h"

//builtins/dispatch.c
int		is_builtin(char *cmd);
int		run_builtin(char **argv, t_env *env);

//builtins/env_edit.c
int		set_env(t_env *env, char *name, char *content);
int		del_env(t_env *env, char *name);

//builtins/ft_echo.c
int		ft_echo(char **argv);

//builtins/ft_pwd.c
int		ft_pwd(void);

//builtins/ft_env.c
int		ft_env(t_env *env);

//builtins/ft_cd.c
int		ft_cd(char **argv, t_env *env);

//builtins/ft_export.c
int		ft_export(char **argv, t_env *env);

//builtins/export_print.c
void	export_print(t_env *env);

//builtins/ft_unset.c
int		ft_unset(char **argv, t_env *env);

//builtins/ft_exit.c
int		ft_exit(char **argv, t_env *env);

#endif
