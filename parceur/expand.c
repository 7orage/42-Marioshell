#include "lexeur.h"

/*
		'...' aucune expansion (expand() n'est jamais appelee)
		"..." expansion, identique a hors quotes
		$NAME NAME = [A-Za-z_][A-Za-z0-9_]*, inexistante = vide
		$?	 exit status
		$1..$9 parametre positionnel = vide
		$ seul le '$' reste litteral
*/

# define BUF_MAX 4096

// AJOUTE s DANS buffer A PARTIR DE *j (borne sur BUF_MAX)
static void	buf_add_str(char *buffer, int *j, char *s)
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

// LONGUEUR DU NOM DE VARIABLE QUI SUIT LE '$' (s pointe sur le '$')
static int	var_len(char *s)
{
	int	k;

	k = 1;
	if (!ft_isalpha(s[k]) && s[k] != '_')
		return (0);
	while (ft_isalnum(s[k]) || s[k] == '_')
		k++;
	return (k - 1);
}

// CHERCHE UNE VARIABLE DANS L'ENV (match exact sur len caracteres)
char	*env_get(t_env *env, char *name, int len)
{
	while (env)
	{
		if (ft_strncmp(env->name, name, len) == 0 && env->name[len] == '\0')
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

// EXPANSE LE '$' SUR LEQUEL raw POINTE, RETOURNE LE NB DE CHARS CONSOMMES
int	expand(char *raw, char *buffer, int *j, t_env *env)
{
	int		len;
	char	*value;

	if (raw[1] == '?')
	{
		value = env_get(env, "?", 1);
		if (!value)
			value = "0";
		return (buf_add_str(buffer, j, value), 2);
	}
	if (ft_isdigit(raw[1]))
		return (2);
	len = var_len(raw);
	if (len == 0)
		return (buf_add_str(buffer, j, "$"), 1);
	buf_add_str(buffer, j, env_get(env, raw + 1, len));
	return (len + 1);
}
