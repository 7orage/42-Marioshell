/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 16:05:47 by lheteau           #+#    #+#             */
/*   Updated: 2026/05/13 13:41:25 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t elementCount, size_t elementSize)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)malloc(elementCount * elementSize);
	i = 0;
	if (p == NULL)
		return (p);
	while (i < elementCount * elementSize)
	{
		p[i] = 0;
		i++;
	}
	return (p);
}
