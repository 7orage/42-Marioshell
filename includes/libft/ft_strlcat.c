/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:42:50 by lheteau           #+#    #+#             */
/*   Updated: 2025/11/17 09:20:55 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dst);
	if (siz == 0 || i >= siz)
		return (siz + ft_strlen(src));
	j = 0;
	while (src[j] && (i + j < siz - 1))
	{
		dst[i + j] = src[j];
		j++;
	}
	dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
/*
int main(void)
{
    char    dest[30] = "CCCCCCCCCCCCCCC";
    char	*src = "AAAAAAAAA";
	char    dest1[30] = "CCCCCCCCCCCCCCC";
    char	*src1 = "AAAAAAAAA";

    printf("Lenght du tt : %lu\n", ft_strlcat(dest, src, 6));
    printf("Dest final : %s\n\n", dest);
	printf("Lenght du tt (off) : %lu\n", strlcat(dest1, src1, 6));
    printf("Dest final : %s\n\n", dest1);
}*/
