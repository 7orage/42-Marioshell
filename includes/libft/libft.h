/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:10:52 by lheteau           #+#    #+#             */
/*   Updated: 2025/11/26 14:47:30 by lheteau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

//# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
//# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
//# include <string.h>
//# include <bsd/string.h>

char				*ft_strchr(const char *s, int c);
char				*ft_strdup(const char *s);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, const char *s2);
char				*ft_itoa(int n);

char				**ft_split(char const *s, char c);

size_t				ft_strlen(const char *str);

int					ft_atoi(const char *nptr);
int					ft_isalnum(int c);
int					ft_isalpha(int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_isdigit(int c);

void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);

void				*ft_calloc(size_t elementCount, size_t elementSize);

#endif
