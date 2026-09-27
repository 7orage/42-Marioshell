/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmoussa <anmoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 01:57:14 by anmoussa          #+#    #+#             */
/*   Updated: 2026/09/27 01:57:15 by anmoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
err_sys		-> SYSTEM ERROR (pipe, fork, malloc), RETURNS 1
err_file	-> ERROR ON A FILE, RETURNS 0 SO A CALLER CAN GIVE UP
err_cmd		-> ERROR ON A COMMAND, RETURNS THE WANTED EXIT CODE
*/

int	err_sys(char *who)
{
	int	errb;

	errb = errno;
	ft_putstr_fd("minishell: ", 2);
	errno = errb;
	perror(who);
	return (1);
}

int	err_file(char *file)
{
	char	*strerr;

	strerr = strerror(errno);
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerr, 2);
	return (0);
}

int	err_cmd(char *cmd, char *msg, int code)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(msg, 2);
	return (code);
}
