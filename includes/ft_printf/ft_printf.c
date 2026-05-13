/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:03:09 by lheteau           #+#    #+#             */
/*   Updated: 2025/12/05 15:51:46 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *chaine, ...)
{
	va_list	args;
	int		i;
	int		nump;

	nump = 0;
	i = 0;
	va_start(args, chaine);
	while (chaine[i])
	{
		if (chaine[i] == '%')
		{
			nump += ft_find_conv(chaine[i + 1], &args);
			i += 2;
		}
		else
		{
			write(1, &chaine[i], 1);
			i++;
			nump++;
		}
	}
	va_end(args);
	return (nump);
}
