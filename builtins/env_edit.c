#include "minishell.h"

/*
same_name	-> EXACT NAME COMPARISON, SO USER NEVER MATCHES USERNAME
new_node	-> BUILD ONE ENV NODE, content MAY BE NULL
set_env		-> CREATE THE VARIABLE OR OVERWRITE IT
del_env		-> UNLINK ONE VARIABLE
*/

static int	same_name(char *a, char *b)
{
	if (!a || !b)
		return (0);
	return (!ft_strncmp(a, b, ft_strlen(b) + 1));
}

static t_env	*new_node(char *name, char *content)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->content = NULL;
	node->next = NULL;
	node->name = ft_strdup(name);
	if (!node->name)
		return (free(node), NULL);
	if (content)
		node->content = ft_strdup(content);
	return (node);
}

int	set_env(t_env *env, char *name, char *content)
{
	if (!env)
		return (0);
	while (env)
	{
		if (same_name(env->name, name))
		{
			free(env->content);
			env->content = NULL;
			if (content)
				env->content = ft_strdup(content);
			return (1);
		}
		if (!env->next)
			break ;
		env = env->next;
	}
	env->next = new_node(name, content);
	return (env->next != NULL);
}

int	del_env(t_env *env, char *name)
{
	t_env	*dead;

	while (env && env->next)
	{
		if (same_name(env->next->name, name))
		{
			dead = env->next;
			env->next = dead->next;
			free(dead->name);
			free(dead->content);
			free(dead);
			return (1);
		}
		env = env->next;
	}
	return (0);
}
