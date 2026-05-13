/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:26:34 by lheteau           #+#    #+#             */
/*   Updated: 2025/11/24 15:39:35 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned const char	*psrc;
	unsigned char		*pdest;

	psrc = src;
	pdest = dest;
	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		pdest[i] = psrc[i];
		i++;
	}
	return (dest);
}
/*
int	main(void int argc, char **argv)
{
	//(void)argc;
	size_t	n;
	char	s1[] = "abcdefghijklmno";
	char	s12[] = "abcdefghijklmno";
	char	s2[] = "abcdefghijklmno";
	char	s22[] = "abcdefghijklmno";
	char	s23[] = "abcdefghijklmno";

	
	n = 10;
	//EX1
	ft_memcpy(s1, s1+5, n);
	printf("Avec ma fonction (dest): %s\n", s1);
	memcpy(s12, s12+5, n);
	printf("Avec la fonction off(dest): %s\n\n", s12);
	//EX2
	ft_memcpy(s2+5, s2, n);
	printf("Avec ma fonction (dest): %s\n", s2);
	memcpy(s22+5, s22, n);
	printf("Avec la fonction off(dest): %s\n", s22);
	memmove(s23+5, s23, n);
	printf("Avec la fonction off(dest): %s\n", s23);
	
	//ARGV
	//printf("%p\n", memcpy(argv[1], argv[2], n));
	//printf("Avec la fonction off (dest): %s\n", argv[1]);
	//printf("(source): %s", argv[2]);
}*/
