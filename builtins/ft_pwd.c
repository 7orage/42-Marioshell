/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmoussa <anmoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 01:56:37 by anmoussa          #+#    #+#             */
/*   Updated: 2026/09/27 01:56:38 by anmoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
ft_pwd	-> PRINT THE WORKING DIRECTORY
*/

int	ft_pwd(void)
{
	char	*buf;

	buf = getcwd(NULL, 0);
	if (!buf)
		return (err_cmd("pwd", strerror(errno), 1));
	ft_putendl_fd(buf, 1);
	free(buf);
	return (0);
}
