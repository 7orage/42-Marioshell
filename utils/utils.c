#include "minishell.h"

/*
free_tab		-> FREE A NULL TERMINATED ARRAY OF STRINGS
is_identifier	-> IS THIS A VALID SHELL VARIABLE NAME ?
*/

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return ;
	while (tab[i])
	{
		if (tab[i] != NULL)
			free(tab[i]);
		i++;
	}
	free(tab);
}

int	is_identifier(char *name)
{
	int	i;

	if (!name || !*name)
		return (0);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (0);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
