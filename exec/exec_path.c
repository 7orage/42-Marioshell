#include "minishell.h"

/*
try_dirs	-> LOOK FOR THE COMMAND IN EACH PATH DIRECTORY
find_path	-> FULL PATH OF THE COMMAND, TO FREE
is_exported	-> A VALID IDENTIFIER GOES TO EXECVE, "?" DOES NOT
env_size	-> HOW MANY EXPORTABLE VARIABLES
env_to_tab	-> LINKED LIST TO CHAR ** FOR EXECVE
*/

static char	*try_dirs(char **dirs, char *cmd)
{
	char	*tmp;
	char	*full;
	int		i;

	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i], "/");
		if (!tmp)
			return (NULL);
		full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!full)
			return (NULL);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}

char	*find_path(char *cmd, t_env *env)
{
	char	**dirs;
	char	*path;
	char	*res;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path = find_env(env, "PATH", 4);
	if (!path || !*path)
		return (NULL);
	dirs = ft_split(path, ':');
	if (!dirs)
		return (NULL);
	res = try_dirs(dirs, cmd);
	free_tab(dirs);
	return (res);
}

static int	is_exported(t_env *var)
{
	if (!var->content)
		return (0);
	return (is_identifier(var->name));
}

static int	env_size(t_env *env)
{
	int	n;

	n = 0;
	while (env)
	{
		if (is_exported(env))
			n++;
		env = env->next;
	}
	return (n);
}

char	**env_to_tab(t_env *env)
{
	char	**tab;
	char	*tmp;
	int		i;

	tab = ft_calloc(env_size(env) + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	i = 0;
	while (env)
	{
		if (is_exported(env))
		{
			tmp = ft_strjoin(env->name, "=");
			if (!tmp)
				return (free_tab(tab), NULL);
			tab[i] = ft_strjoin(tmp, env->content);
			free(tmp);
			if (!tab[i])
				return (free_tab(tab), NULL);
			i++;
		}
		env = env->next;
	}
	return (tab);
}
