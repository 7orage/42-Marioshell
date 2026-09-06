#include "lexeur.h"

/*
bufdup		-> COPY STR IN BUFFER
varlen		-> STRLEN OF THE VAR
find_env	-> FIND THE VAR IN THE LIST
expand		-> MANAGE EXPAND
*/

static void	bufdup(char *buffer, int *j, char *s)
{
	int	k;

	k = 0;
	if (!s)
		return ;
	while (s[k] && *j < BUF_MAX - 1)
	{
		buffer[*j] = s[k];
		(*j)++;
		k++;
	}
}

static int	varlen(char *s)
{
	int	k;

	k = 1;
	if (!ft_isalpha(s[k]) && s[k] != '_')
		return (0);
	while (ft_isalnum(s[k]) || s[k] == '_')
		k++;
	return (k - 1);
}

char	*find_env(t_env *env, char *name, int len)
{
	while (env)
	{
		if (ft_strncmp(env->name, name, len) == 0 && env->name[len] == '\0')
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

int	expand(char *raw, char *buffer, int *j, t_env *env)
{
	int		len;
	char	*value;

	if (raw[1] == '?')
	{
		value = find_env(env, "?", 1);
		if (!value)
			value = "0";
		return (bufdup(buffer, j, value), 2);
	}
	if (ft_isdigit(raw[1]))
		return (2);
	len = varlen(raw);
	if (len == 0)
		return (bufdup(buffer, j, "$"), 1);
	bufdup(buffer, j, find_env(env, raw + 1, len));
	return (len + 1);
}
