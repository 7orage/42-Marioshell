#ifndef ENVP_LIST_H
# define ENVP_LIST_H


typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*next;
}					t_env;

//envp_list.c
t_env	*envp_list(char **envp);
void	free_list(t_env *env);

#endif