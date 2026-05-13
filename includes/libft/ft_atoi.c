/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:25:13 by lheteau           #+#    #+#             */
/*   Updated: 2025/11/17 08:54:49 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	i;
	int	s;
	int	resultat;

	i = 0;
	s = 1;
	resultat = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == 32)
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			s *= -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		resultat = resultat * 10 + nptr[i] - 48;
		i++;
	}
	return (resultat * s);
}
/*
int     main(void)
{
    printf("FT_ATOI :%d\n", ft_atoi(escape[5]));
    printf("ATOI OFF :%d", atoi(escape[5]));
}*/