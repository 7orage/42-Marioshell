/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 16:08:15 by lheteau           #+#    #+#             */
/*   Updated: 2025/11/24 12:12:33 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*app;
	int		i;

	i = 0;
	app = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!app)
		return (NULL);
	while (s[i])
	{
		app[i] = f(i, s[i]);
		i++;
	}
	app[i] = '\0';
	return (app);
}
