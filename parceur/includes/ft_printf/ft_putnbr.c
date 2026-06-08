/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 16:20:42 by lheteau           #+#    #+#             */
/*   Updated: 2026/05/13 13:42:21 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr(int n)
{
	int	nbr;

	nbr = n;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return (11);
	}
	if (n < 0 && n != -2147483648)
	{
		n *= -1;
		write(1, "-", 1);
	}
	if (n >= 0 && n <= 9)
	{
		n += 48;
		write(1, &n, 1);
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	return (ft_numlen(nbr));
}

int	ft_putnbr_unsigned(unsigned int n)
{
	if (n <= 9)
	{
		n += 48;
		write(1, &n, 1);
		n -= 48;
	}
	else
	{
		ft_putnbr_unsigned(n / 10);
		ft_putnbr_unsigned(n % 10);
	}
	return (ft_numlen_unsigned(n));
}

int	ft_putnbrbase(int n, char c)
{
	unsigned int	nbr;
	char			*hexa;
	int				len;

	len = 0;
	if (c == 'x')
		hexa = "0123456789abcdef";
	else if (c == 'X')
		hexa = "0123456789ABCDEF";
	nbr = n;
	if (nbr < 16)
		len += write(1, &hexa[nbr], 1);
	else
	{
		len += ft_putnbrbase(nbr / 16, c);
		len += ft_putnbrbase(nbr % 16, c);
	}
	return (len);
}

int	ft_putnbr_pointeur(uintptr_t p)
{
	char	*hexa;
	int		len;

	len = 0;
	hexa = "0123456789abcdef";
	if (p < 16)
		len += write(1, &hexa[p], 1);
	else
	{
		len += ft_putnbr_pointeur(p / 16);
		len += ft_putnbr_pointeur(p % 16);
	}
	return (len);
}
