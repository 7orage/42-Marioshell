/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_conv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 12:25:32 by lheteau           #+#    #+#             */
/*   Updated: 2025/12/05 16:15:44 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

//%c Prints a single character.
//%s Prints a string (as defined by the common C convention).
//%p The void * pointer argument has to be printed in hexadecimal format.
//%d Prints a decimal (base 10) number.
//%i Prints an integer in base 10.
//%u Prints an unsigned decimal (base 10) number.
//%x Prints a number in hexadecimal (base 16) lowercase format.
//%X Prints a number in hexadecimal (base 16) uppercase format.
//%% Prints a percent sign.

int	ft_find_conv(char c, va_list *args)
{
	int	nump;

	nump = 0;
	if (c == 'c')
		nump = ft_putchar(va_arg(*args, char *));
	else if (c == 's')
		nump = ft_putstr(va_arg(*args, char *));
	else if (c == 'p')
		nump = ft_putstr_pointeur(va_arg(*args, unsigned long long));
	else if (c == 'd' || c == 'i')
		nump = ft_putnbr(va_arg(*args, int));
	else if (c == 'u')
		nump = ft_putnbr_unsigned(va_arg(*args, unsigned int));
	else if (c == 'x' || c == 'X')
		nump = ft_putnbrbase(va_arg(*args, int), c);
	else if (c == '%')
		nump += write(1, "%", 1);
	return (nump);
}
