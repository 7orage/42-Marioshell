#include "lexeur.h"

/*
cut_quotes		-> SUBCUT, IN QUOTES
cut_unquotes	-> SUBCUT, WITHOUT QUOTES
cut 			-> CUT THE TOKEN PROPERLY
*/

static int	cut_quotes(char *raw_tok, char *buffer, int *j, t_env *env)
{
	int	i;

	i = 1;
	while (raw_tok[i] && raw_tok[i] != raw_tok[0])
	{
		if (raw_tok[0] == '"' && raw_tok[i] == '$')
			i += expand(&raw_tok[i], buffer, j, env);
		else
		{
			buffer[*j] = raw_tok[i];
			i++;
			(*j)++;
		}
	}
	if (raw_tok[i] == raw_tok[0])
		i++;
	return (i);
}

static int	cut_noquotes(char *raw_tok, char *buffer, int *j, t_env *env)
{
	int	i;

	i = 0;
	while (raw_tok[i] && raw_tok[i] != '"' && raw_tok[i] != '\''
		&& !ft_isspace(raw_tok[i]) && !is_delim(raw_tok[i]))
	{
		if (raw_tok[i] == '$')
			i += expand(&raw_tok[i], buffer, j, env);
		else
		{
			buffer[*j] = raw_tok[i];
			i++;
			(*j)++;
		}
	}
	return (i);
}

char	*cut(char *raw_tok, t_env *env, int *initial_i)
{
	char	buffer[4096];
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (raw_tok[i] && !ft_isspace(raw_tok[i]) && !is_delim(raw_tok[i]))
	{
		if (raw_tok[i] == '"' || raw_tok[i] == '\'')
			i += cut_quotes(&raw_tok[i], buffer, &j, env);
		else
			i += cut_noquotes(&raw_tok[i], buffer, &j, env);
	}
	buffer[j] = '\0';
	*initial_i += i;
	return (ft_strdup(buffer));
}
