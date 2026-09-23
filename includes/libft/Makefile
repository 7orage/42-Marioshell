# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/11 17:17:39 by lheteau           #+#    #+#              #
#    Updated: 2026/02/22 20:15:37 by lheteau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:
NAME = libft.a
CC = cc

SRC = ft_atoi.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isdigit.c ft_itoa.c ft_putendl_fd.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c ft_substr.c
OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
CFLAGS = -Wall -Wextra -Werror -fPIC

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o : %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re
