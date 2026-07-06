/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/19 15:21:40 by lheteau           #+#    #+#             */
/*   Updated: 2026/01/24 17:02:49 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
// def of buffer size constant
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

// libraries
# include "../libft/libft.h"
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
//# include <fcntl.h>
//# include <stdio.h>

// functions
char	*get_next_line(int fd);
char	*fill_line(int fd, char **stash, char *buff);
char	*ft_strchrg(const char *s, int c);
size_t	ft_strlen(const char *str);

#endif