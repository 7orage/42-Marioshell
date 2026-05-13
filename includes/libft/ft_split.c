/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 17:14:46 by lheteau           #+#    #+#             */
/*   Updated: 2025/11/26 15:15:02 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_word(char const *s, char c)
{
	int	i;
	int	in_word;
	int	count_word;

	i = 0;
	in_word = 0;
	count_word = 0;
	while (s[i])
	{
		if (s[i] != c && in_word == 0)
		{
			in_word = 1;
			count_word++;
		}
		else if (s[i] == c)
			in_word = 0;
		i++;
	}
	return (count_word);
}

static char	*copy_word(char const *s, char c)
{
	int		i;
	char	*sub;
	char	*ps;

	i = 0;
	ps = (char *)s;
	while (ps[i] && ps[i] != c)
		i++;
	sub = (char *)malloc(sizeof(char) * (i + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while (ps[i] && ps[i] != c)
	{
		sub[i] = ps[i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

static void	*ft_free(char **split, int mot)
{
	int	i;

	i = 0;
	while (i < mot)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}

static char	**ft_conca(char const *s, char c, char **split)
{
	int	i;
	int	mot;
	int	insert;

	i = 0;
	mot = 0;
	insert = 0;
	while (s[i])
	{
		if (s[i] == c)
			insert = 0;
		else if (s[i] != c && insert == 0)
		{
			split[mot] = copy_word(&s[i], c);
			if (!split[mot])
				return (ft_free(split, mot));
			mot++;
			insert = 1;
		}
		i++;
	}
	split[mot] = 0;
	return (split);
}

char	**ft_split(char const *s, char c)
{
	char	**split;

	split = (char **)malloc((count_word(s, c) + 1) * sizeof(char *));
	if (!split)
		return (NULL);
	split = ft_conca(s, c, split);
	return (split);
}
/*
int	main(void)
{
	char **tab;
	int i = 0;

	//printf("%d\n", count_word("ba js n ", ' '));
	//printf("%s\n", copy_word("kalediod     f", ' '));
	tab = ft_split("      split       this for   me  !       ", ' ');
	while (tab[i])
	{
		printf("%s\n", tab[i]);
		i++;
	}
}*/
