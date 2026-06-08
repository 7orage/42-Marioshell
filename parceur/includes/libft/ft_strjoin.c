/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:19:57 by lheteau           #+#    #+#             */
/*   Updated: 2026/05/13 13:41:47 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, const char *s2)
{
	char	*join;
	int		i;
	int		j;

	i = 0;
	j = 0;
	join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (join == NULL)
	{
		free(join);
		return (NULL);
	}
	while (s1[i])
	{
		join[i] = (char)s1[i];
		i++;
	}
	while (s2[j])
		join[i++] = (char)s2[j++];
	join[i] = '\0';
	return (join);
}
/*
int	main(void)
{
	printf("%s", ft_strjoin("le debut", "et la fin"));
}*/
