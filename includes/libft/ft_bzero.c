/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:10:16 by lheteau           #+#    #+#             */
/*   Updated: 2025/11/13 14:20:11 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ps;
	size_t	i;

	ps = s;
	i = 0;
	while (i < n)
	{
		ps[i] = '\0';
		i++;
	}
}
/*
int	main(void)
{
	char buffer[] = "This is a test of the bzero function";

	printf( "Before: %s\n", buffer );
	ft_bzero( buffer+9, (sizeof(char) * 4));
	printf( "After:  %s\n", buffer );
}*/
