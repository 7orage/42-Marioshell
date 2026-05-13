/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 11:28:05 by lheteau           #+#    #+#             */
/*   Updated: 2026/05/07 11:18:42 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	diff_neg(unsigned const char *psrc, unsigned char *pdest, size_t i)
{
	while (i > 0)
	{
		pdest[i] = psrc[i];
		i--;
	}
	pdest[i] = psrc[i];
}

static void	diff_pos(unsigned const char *psrc, unsigned char *pdest,
		size_t i, size_t n)
{
	while (i < n)
	{
		pdest[i] = psrc[i];
		i++;
	}
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned const char	*psrc;
	unsigned char		*pdest;

	psrc = src;
	pdest = dest;
	i = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (src < dest && src + n > dest)
	{
		i = n - 1;
		diff_neg(psrc, pdest, i);
	}
	else
	{
		diff_pos(psrc, pdest, 0, n);
	}
	return (dest);
}
/*
int	main(void)
{
	//(void)argc;
	size_t	n;
	char	s1[] = "abcdefghijklmno";
	char	s12[] = "abcdefghijklmno";
	char	s2[] = "abcdefghijklmno";
	char	s22[] = "abcdefghijklmno";

	
	n = 10;
	//EX1
	ft_memmove(s1, s1+5, n);
	printf("Avec ma fonction (dest): %s\n", s1);
	memmove(s12, s12+5, n);
	printf("Avec la fonction off(dest): %s\n\n", s12);
	//EX2
	ft_memmove(s2+5, s2, n);
	printf("Avec ma fonction (dest): %s\n", s2);
	memmove(s22+5, s22, n);
	printf("Avec la fonction off(dest): %s\n", s22);
	
	//ARGV
	//printf("%p\n", memcpy(argv[1], argv[2], n));
	//printf("Avec la fonction off (dest): %s\n", argv[1]);
	//printf("(source): %s", argv[2]);
}*/
