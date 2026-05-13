/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:49:42 by lheteau           #+#    #+#             */
/*   Updated: 2025/12/08 09:51:54 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static bool	ft_in(char const *set, char c)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (true);
		i++;
	}
	return (false);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		debut;

	i = 0;
	debut = 0;
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	while (ft_in(set, s1[i]) == true)
		i++;
	debut = i;
	i = ft_strlen(s1) - 1;
	while (ft_in(set, s1[i]) == true)
		i--;
	return (ft_substr(s1, debut, i - (debut - 1)));
}
/*
int	main(void)
{
	printf("%s", ft_strtrim("", ""));
}*/