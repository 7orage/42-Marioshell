/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   istype.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmoussa <anmoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 01:55:16 by anmoussa          #+#    #+#             */
/*   Updated: 2026/09/27 01:55:17 by anmoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
is_quotes_closed	-> IS THE QUOTES CLOSED ?
is_delim			-> IS IT A '|' || '<' || '>' ?
ft_isspace			-> IS IT A SPACE ?
*/

int	is_quotes_closed(char *input)
{
	int		i;
	char	quote;

	i = 0;
	quote = 0;
	while (input[i])
	{
		if (!quote && (input[i] == '\'' || input[i] == '"'))
			quote = input[i];
		else if (quote && input[i] == quote)
			quote = 0;
		i++;
	}
	if (quote)
		return (0);
	return (1);
}

int	is_delim(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}
