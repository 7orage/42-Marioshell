#include "minishell.h"

/*
is_n_flag	-> IS IT -n, -nn, -nnnn ? -na IS NOT AN OPTION
ft_echo		-> PRINT THE ARGUMENTS, NEVER FAILS
*/

static int	is_n_flag(char *s)
{
	int	j;

	if (s[0] != '-' || s[1] != 'n')
		return (0);
	j = 1;
	while (s[j] == 'n')
		j++;
	return (s[j] == '\0');
}

int	ft_echo(char **argv)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (argv[i] && is_n_flag(argv[i]))
	{
		newline = 0;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i], 1);
		if (argv[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", 1);
	return (0);
}
