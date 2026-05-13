/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:02:06 by lheteau           #+#    #+#             */
/*   Updated: 2025/11/24 12:13:02 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ps;
	int				i;

	ps = (unsigned char *)s;
	i = 0;
	if (n == 0)
		return (NULL);
	while (ps[i] != (unsigned char)c % 256 && n != 1)
	{
		i++;
		n--;
	}
	if (ps[i] == (unsigned char)c % 256)
		return ((void *)&ps[i]);
	else
		return (NULL);
}
/*
int	main(void)
{
	char s[] = {0, 1, 2 ,3 ,4 ,5};

	printf( "La chaine finale : %p\n", ft_memchr(s, 2, 3));
	printf( "La chaine off : %p", memchr(s, 2, 3));
}*/