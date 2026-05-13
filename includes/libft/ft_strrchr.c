/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 12:04:20 by lheteau           #+#    #+#             */
/*   Updated: 2025/11/17 19:34:42 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (c % 256 == '\0' || c % 256 == 0)
		return ((char *)&s[ft_strlen(s)]);
	while (s[i])
	{
		if (s[i] == c % 256)
		{
			j = 1;
			while (s[i + j] != c % 256)
			{
				if (s[i + j] == 0)
					return ((char *)&s[i]);
				j++;
			}
			i++;
		}
		else
		i++;
	}
	return (NULL);
}
/*
int     main(void)
{
//    char    *test = "abcdefaghij";
//    char    *result = ft_strrchr(test, 'a');
//	char s[] = "tripouille";
	//char s2[] = "ltripouiel";
	//char s3[] = "";

    printf( "La chaine finale : %s\n", ft_strrchr("teste", 1024));
	printf( "La chaine off : %s", strrchr("teste", 1024));
}*/
