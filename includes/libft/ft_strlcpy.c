/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:33:39 by lheteau           #+#    #+#             */
/*   Updated: 2025/11/17 18:50:25 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t		i;

	i = 0;
	if (size > 0)
	{
		while (src[i] && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = '\0';
	}
	return (ft_strlen(src));
}
/*
int main(void)
{
	//char    src[] = "Testons la fonction";
	char    dest[10] = "hhs";
	//char    src2[] = "Testons la fonction";
	char    dest2[10] = "hhs";
 
	//char	*str = "";
	
	//printf("Taille de dest: %lu\n", sizeof(dest));
	printf("Fonction (t src): %lu\n", ft_strlcpy(dest, "", 15));
	printf("Dest final: %s\n\n", dest);

	//printf("Taille de dest: %lu\n", sizeof(dest2));
	printf("Fonction off(t src): %lu\n", strlcpy(dest2, "", 15));
	printf("Dest final: %s", dest2);
}*/