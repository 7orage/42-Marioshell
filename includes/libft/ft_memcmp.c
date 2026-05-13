/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 14:25:12 by lheteau           #+#    #+#             */
/*   Updated: 2025/11/24 12:13:17 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int		r;
	size_t	i;

	i = 0;
	while (i < n)
	{
		r = *(unsigned char *)s1++ - *(unsigned char *)s2++;
		if (r != 0)
			return (r);
		i++;
	}
	return (0);
}

/*
int	main(void)
{
	//char s[] = {-128, 0, 127, 0};
	char s2[] = {0, 0, 127, 0};
	char s3[] = {0, 0, 42, 0};

	printf("%d\n", ft_memcmp(s2, s3, 4));
	printf("%d", memcmp(s2, s3, 4));
}*/