/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:20:59 by lheteau           #+#    #+#             */
/*   Updated: 2025/11/24 16:17:14 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (little[j] == 0)
		return ((char *)&big[i]);
	while (big[i] && i < len)
	{
		j = 0;
		while (big[i + j] == little[j] && i + j < len)
		{
			if (j == ft_strlen(little) - 1)
				return ((char *)&big[i]);
			j++;
		}
		i++;
	}
	return (NULL);
}
/*
int     main(void)
{
	char haystack[30] = "aaabcabcd";

    printf("Ma fonction :%s\n", ft_strnstr(haystack, "cd", 8));
	printf("Fonction off :%s", strnstr(haystack, "cd", 8));

}*/