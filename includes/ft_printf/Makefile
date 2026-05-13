# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lheteau <lheteau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/24 16:28:54 by lheteau           #+#    #+#              #
#    Updated: 2026/02/22 20:15:51 by lheteau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:
NAME = libftprintf.a

SRC = ft_printf.c ft_find_conv.c ft_putnbr.c ft_putstr.c ft_libft.c
OBJ_DIR = obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -fPIC

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $(OBJ)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJ)
	rm -rf $(OBJ_DIR)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re
