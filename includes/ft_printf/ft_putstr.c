/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 16:20:32 by lheteau           #+#    #+#             */
/*   Updated: 2025/12/05 15:51:58 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	while (s[i])
		i++;
	write(1, s, i);
	return (i);
}

int	ft_putstr_pointeur(unsigned long long p)
{
	int	i;

	i = 0;
	if (!p)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	i += 2;
	i += ft_putnbr_pointeur(p);
	return (i);
}
