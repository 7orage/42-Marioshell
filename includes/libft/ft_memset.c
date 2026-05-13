/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 16:39:22 by lheteau           #+#    #+#             */
/*   Updated: 2025/11/13 14:21:15 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void	*s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ps;

	ps = s;
	i = 0;
	while (i < n)
	{
		ps[i] = c;
		i++;
	}
	return (s);
}
/*
int	main(void)
{
	char str[] = "This is a test of the memset function";
	
	printf( "Before: %s\n", str );
	ft_memset( str, '*', (sizeof(char) * 4));
	printf( "After:  %s\n", str );
}*/
