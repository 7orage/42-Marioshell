/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/28 11:35:36 by lheteau           #+#    #+#             */
/*   Updated: 2026/01/29 12:23:31 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

//# include <limits.h>
# include "../libft/libft.h"
# include <stdarg.h>
# include <stdint.h>
//# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *chaine, ...) __attribute__((format(printf, 1,
					2)));
int		ft_find_conv(char c, va_list *args);
int		ft_putstr(char *s);
int		ft_putstr_pointeur(unsigned long long p);
int		ft_numlen(int n);
int		ft_numlen_unsigned(unsigned int n);
int		ft_putnbr(int n);
int		ft_putnbr_unsigned(unsigned int n);
int		ft_putnbrbase(int n, char c);
int		ft_putnbr_pointeur(uintptr_t n);
int		ft_putchar(char *c);

size_t	ft_strlen(const char *str);

#endif
