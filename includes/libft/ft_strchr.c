/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 11:08:54 by lheteau           #+#    #+#             */
/*   Updated: 2025/11/24 12:13:40 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c % 256)
		i++;
	if (s[i] == c % 256)
		return ((char *)&s[i]);
	else
		return (NULL);
}
/*
int	main(void)
{
	char    *test = "tripouille";
	//int     c = 's';
	char    *result = ft_strchr(test, 't' + 256 * 2);
	char    *result1 = strchr(test, 't' + 256);

	printf( "La chaine finale : %s\n", result);
	printf( "La chaine finale (off): %s", result1);
}*/