/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/21 14:50:36 by lheteau           #+#    #+#             */
/*   Updated: 2025/11/24 15:43:28 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numlen(int n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len++;
		n *= -1;
	}
	if (n == 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*number;
	int		diz;
	int		len;
	long	num;

	num = n;
	len = ft_numlen(n);
	number = malloc(sizeof(char) * (len + 1));
	if (number == NULL)
		return (NULL);
	number[0] = 0;
	if (num < 0)
		num *= -1;
	diz = len - 1;
	while (diz >= 0)
	{
		number[diz] = (num % 10) + '0';
		num /= 10;
		diz--;
	}
	if (n < 0)
		number[0] = '-';
	number[len] = '\0';
	return (number);
}
/*
int	main(void)
{
	char	*tab;

	tab = ft_itoa(-2147483648);
	printf("%d\n", ft_numlen(-2147483648));
	printf("%s\n", ft_itoa(-2147483648));
	printf("%c", tab[2]);
}*/
