/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anmoussa <anmoussa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/27 01:56:02 by anmoussa          #+#    #+#             */
/*   Updated: 2026/09/27 01:56:03 by anmoussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "common.h"

//utils/error.c
int		err_sys(char *who);
int		err_file(char *file);
int		err_cmd(char *cmd, char *msg, int code);

//utils/utils.c
void	free_tab(char **tab);
int		is_identifier(char *name);
void	close_std(void);

#endif
