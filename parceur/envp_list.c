#include "parceur.h"

/*
new_list		-> ADD A NODE
insert_end_list	-> PUT THE NODE AT THE END
free_list		-> FREE THE LIST
envp_list		-> ENVP LIST MANAGE
*/

static t_env	*new_list(char *name, char *content)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = name;
	new->content = content;
	new->next = NULL;
	return (new);
}

static int	insert_end_list(t_env **first, char *name, char *content)
{
	t_env	*new_node;
	t_env	*current;

	if (*first == NULL)
	{
		*first = new_list(name, content);
		if (!*first)
			return (0);
		return (1);
	}
	current = *first;
	while (current->next)
		current = current->next;
	new_node = new_list(name, content);
	if (!new_node)
		return (0);
	current->next = new_node;
	return (1);
}

void	free_list(t_env *env)
{
	t_env	*temp;

	while (env)
	{
		temp = env;
		env = env->next;
		free(temp->name);
		free(temp);
	}
}

t_env	*envp_list(char **envp)
{
	t_env	*env;
	char	*name;
	int		i;
	int		j;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j] && envp[i][j] != '=')
			j++;
		name = ft_strdup(envp[i]);
		if (!name)
			return (NULL);
		name[j] = 0;
		if (!insert_end_list(&env, name, envp[i] + (j + 1)))
			free(name);
		i++;
	}
	return (env);
}
